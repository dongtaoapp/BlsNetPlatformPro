#pragma once
#define BOOST_REGEX_NO_LIB
#define BOOST_DATE_TIME_SOURCE
//#define BOOST_SYSTEM_NO_LIB
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include ".\common_global.h"


using namespace boost;
using namespace boost::asio;

namespace jysoft{ namespace utility 
{
	/**
	* 时钟定时器
	*/
    class Q_DECL_EXPORT CEmulateTimer
	{
	public:
		template<typename  F>
		CEmulateTimer( short millisec, F func) : f(func), millisecTime(millisec), t(ios, posix_time::millisec(millisec)) 
		{
			//注册回调函数
			t.async_wait(boost::bind(&CEmulateTimer::call_func, this, boost::asio::placeholders::error));
		};
		virtual ~CEmulateTimer(void)
		{
			killTimer();
		};
	protected:
		io_service  ios;
		short       millisecTime;
		boost::function<void()>  f;
		deadline_timer    t;
	private:
		thread_group   tg;
	public:
		void startTimer()
		{
			tg.create_thread( boost::bind(&io_service::run, &ios) );

		}
		void killTimer()
		{
			ios.stop();
			tg.join_all();
			bool bThread = tg.is_this_thread_in();
			short sSize = tg.size();
		};
	protected:
		void call_func(const boost::system::error_code &)
		{
			//调用function对象
			f();
			//设置定时器的终止时间+millisecTime秒之后
			t.expires_at( t.expires_at() + boost::posix_time::millisec(millisecTime));
			//再次启动定时器， 异步等待
			t.async_wait(boost::bind(&CEmulateTimer::call_func, this, boost::asio::placeholders::error));
		}
	};
}}

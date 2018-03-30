#pragma once
#include <string>
#include ".\common_global.h"


namespace jysoft {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ˫�����ӽӿڻ���
	�����ˣ�	 hjg
	����ʱ�䣺   2016/8/20
	���ܣ�       ����˫�����ӵĲ�������
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS IBedirecteLinksVir
	{
	public:
		IBedirecteLinksVir(void);
		virtual ~IBedirecteLinksVir(void);
	protected:
		IBedirecteLinksVir            *m_pNextInterface;    //�¸��ӿ�
		IBedirecteLinksVir            *m_pPreInterface;     //�ϸ��ӿ�
	public:
		//�����¸�������ʾ�ؼ��ӿ�
		void SetNextInterfacePtr(IBedirecteLinksVir *pNextInterface);
		//�����ϸ��ӿ�
		inline void SetPreviouInterfacePtr(IBedirecteLinksVir *pPreInterface) { m_pPreInterface = pPreInterface;};
		//�����¸��ӿ�
		inline IBedirecteLinksVir * GetNextInterfacePtr() { return m_pNextInterface;};
		//�����ϸ��ӿ�
		inline IBedirecteLinksVir * GetPreviouInterfacePtr() { return m_pPreInterface;};
	public:
		//���ؽӿ������ͷ
		IBedirecteLinksVir * GetHeaderInterfacePtr();
		//�Ƴ��ƶ��Ľӿ�
		static IBedirecteLinksVir * RemoveInterfacePtr(IBedirecteLinksVir *pOrgInterfacePtr, IBedirecteLinksVir *pRmvInterface);
	public:
		virtual bool isKindOf(const std::string &className) = 0;
	};
}

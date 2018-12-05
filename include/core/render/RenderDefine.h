#pragma once

namespace Liar
{
	enum RenderQueueDefine
	{
		/** �����͸����Ⱦ���б�ǡ�*/
		RENDERQUEUE_OPAQUE,
		/** ͸�������Ⱦ���б�� */
		RENDERQUEUE_TRANSPARENT
	};

	/**��Ⱦ״̬*/
	enum RenderModeDefine
	{
		/**��Ⱦ״̬_��͸����*/
		RENDERMODE_OPAQUE = 1,
		/**��Ⱦ״̬_��͸��_˫�档*/
		RENDERMODE_OPAQUEDOUBLEFACE,
		/**��Ⱦ״̬_͸�����ԡ�*/
		RENDERMODE_CUTOUT,
		/**��Ⱦ״̬_͸������_˫�档*/
		RENDERMODE_CUTOUTDOUBLEFACE,
		/**��Ⱦ״̬_ֻ�����_͸����ϡ�*/
		RENDERMODE_DEPTHREAD_TRANSPARENT,
		/**��Ⱦ״̬_ֻ�����_͸�����_˫�档*/
		RENDERMODE_DEPTHREAD_TRANSPARENTDOUBLEFACE,
		/**��Ⱦ״̬_ֻ�����_��ɫ����ϡ�*/
		RENDERMODE_DEPTHREAD_ADDTIVE,
		/**��Ⱦ״̬_ֻ�����_��ɫ�����_˫�档*/
		RENDERMODE_DEPTHREAD_ADDTIVEDOUBLEFACE,
		/**��Ⱦ״̬_�����_͸����ϡ�*/
		RENDERMODE_NONDEPTH_TRANSPARENT,
		/**��Ⱦ״̬_�����_͸�����_˫�档*/
		RENDERMODE_NONDEPTH_TRANSPARENTDOUBLEFACE,
		/**��Ⱦ״̬_�����_��ɫ����ϡ�*/
		RENDERMODE_NONDEPTH_ADDTIVE,
		/**��Ⱦ״̬_͸����ϡ�*/
		RENDERMODE_TRANSPARENT,
		/**��Ⱦ״̬_�����_��ɫ�����_˫�档*/
		RENDERMODE_NONDEPTH_ADDTIVEDOUBLEFACE,
		/**��Ⱦ״̬_͸�����_˫�档*/
		RENDERMODE_TRANSPARENTDOUBLEFACE,
		/**��Ⱦ״̬_��ɫ����ϡ�*/
		RENDERMODE_ADDTIVE,
		/**��Ⱦ״̬_��ɫ�����_˫�档*/
		RENDERMODE_ADDTIVEDOUBLEFACE
	};
}
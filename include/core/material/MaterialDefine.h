#pragma once

namespace Liar
{
	enum CullType
	{
		/**�޳�ö��_���޳���*/
		CULL_NONE = 0,
		/**�޳�ö��_�޳����档*/
		CULL_FRONT,
		/**�޳�ö��_�޳����档*/
		CULL_BACK
	};

	enum BlendType
	{
		/**���ö��_���á�*/
		BLEND_DISABLE = 0,
		/**���ö��_����_RGB��Alphaͳһ��ϡ�*/
		BLEND_ENABLE_ALL,
		/**���ö��_����_RGB��Alpha������ϡ�*/
		BLEND_ENABLE_SEPERATE
	};

	/*��ϲ���ö��*/
	enum BlendParam
	{
		/**��ϲ���ö��_��,����RGB(0,0,0),Alpha:(1)��*/
		BLENDPARAM_ZERO = 0,
		/**��ϲ���ö��_һ,����RGB(1,1,1),Alpha:(1)��*/
		BLENDPARAM_ONE = 1,
		/**��ϲ���ö��_Դ��ɫ,����RGB(Rs, Gs, Bs)��Alpha(As)��*/
		BLENDPARAM_SRC_COLOR = 0x0300,
		/**��ϲ���ö��_һ��Դ��ɫ,����RGB(1-Rs, 1-Gs, 1-Bs)��Alpha(1-As)��*/
		BLENDPARAM_ONE_MINUS_SRC_COLOR = 0x0301,
		/**��ϲ���ö��_Դ͸��,��:RGB(As, As, As),Alpha(1-As)��*/
		BLENDPARAM_SRC_ALPHA = 0x0302,
		/**��ϲ���ö��_һ��Դ������,��:RGB(1-As, 1-As, 1-As),Alpha(1-As)��*/
		BLENDPARAM_ONE_MINUS_SRC_ALPHA = 0x0303,
		/**��ϲ���ö��_Ŀ�갢����������RGB(Ad, Ad, Ad),Alpha(Ad)��*/
		BLENDPARAM_DST_ALPHA = 0x0304,
		/**��ϲ���ö��_һ��Ŀ�갢����,����RGB(1-Ad, 1-Ad, 1-Ad),Alpha(Ad)��*/
		BLENDPARAM_ONE_MINUS_DST_ALPHA = 0x0305,
		/**��ϲ���ö��_Ŀ����ɫ,����RGB(Rd, Gd, Bd),Alpha(Ad)��*/
		BLENDPARAM_DST_COLOR = 0x0306,
		/**��ϲ���ö��_һ��Ŀ����ɫ,����RGB(1-Rd, 1-Gd, 1-Bd)��Alpha(1-Ad)��*/
		BLENDPARAM_ONE_MINUS_DST_COLOR = 0x0307,
		/**��ϲ���ö��_���������ͣ�����RGB(min(As, 1 - Ad), min(As, 1 - Ad), min(As, 1 - Ad)),Alpha(1)��*/
		BLENDPARAM_SRC_ALPHA_SATURATE = 0x0308
	};

	/*��Ϸ���ö��*/
	enum BlendQuation
	{
		/**��Ϸ���ö��_�ӷ�,����source + destination*/
		BLENDEQUATION_ADD,
		/**��Ϸ���ö��_����������source - destination*/
		BLENDEQUATION_SUBTRACT,
		/**��Ϸ���ö��_�������������destination - source*/
		BLENDEQUATION_REVERSE_SUBTRACT
	};

	/*��Ȳ��Ժ���ö��*/
	enum DepthTest
	{
		/**��Ȳ��Ժ���ö��_�ر���Ȳ��ԡ�*/
		DEPTHTEST_OFF,
		/**��Ȳ��Ժ���ö��_�Ӳ�ͨ����*/
		DEPTHTEST_NEVER = 0x0200,
		/**��Ȳ��Ժ���ö��_С��ʱͨ����*/
		DEPTHTEST_LESS,
		/**��Ȳ��Ժ���ö��_����ʱͨ����*/
		DEPTHTEST_EQUAL,
		/**��Ȳ��Ժ���ö��_С�ڵ���ʱͨ����*/
		DEPTHTEST_LEQUAL,
		/**��Ȳ��Ժ���ö��_����ʱͨ����*/
		DEPTHTEST_GREATER,
		/**��Ȳ��Ժ���ö��_������ʱͨ����*/
		DEPTHTEST_NOTEQUAL,
		/**��Ȳ��Ժ���ö��_���ڵ���ʱͨ����*/
		DEPTHTEST_GEQUAL,
		/**��Ȳ��Ժ���ö��_����ͨ����*/
		DEPTHTEST_ALWAYS
	};
}
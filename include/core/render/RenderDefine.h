#pragma once

namespace Liar
{
	enum RenderQueueDefine
	{
		/** 定义非透明渲染队列标记。*/
		RENDERQUEUE_OPAQUE,
		/** 透明混合渲染队列标记 */
		RENDERQUEUE_TRANSPARENT
	};

	/**渲染状态*/
	enum RenderModeDefine
	{
		/**渲染状态_不透明。*/
		RENDERMODE_OPAQUE = 1,
		/**渲染状态_不透明_双面。*/
		RENDERMODE_OPAQUEDOUBLEFACE,
		/**渲染状态_透明测试。*/
		RENDERMODE_CUTOUT,
		/**渲染状态_透明测试_双面。*/
		RENDERMODE_CUTOUTDOUBLEFACE,
		/**渲染状态_只读深度_透明混合。*/
		RENDERMODE_DEPTHREAD_TRANSPARENT,
		/**渲染状态_只读深度_透明混合_双面。*/
		RENDERMODE_DEPTHREAD_TRANSPARENTDOUBLEFACE,
		/**渲染状态_只读深度_加色法混合。*/
		RENDERMODE_DEPTHREAD_ADDTIVE,
		/**渲染状态_只读深度_加色法混合_双面。*/
		RENDERMODE_DEPTHREAD_ADDTIVEDOUBLEFACE,
		/**渲染状态_无深度_透明混合。*/
		RENDERMODE_NONDEPTH_TRANSPARENT,
		/**渲染状态_无深度_透明混合_双面。*/
		RENDERMODE_NONDEPTH_TRANSPARENTDOUBLEFACE,
		/**渲染状态_无深度_加色法混合。*/
		RENDERMODE_NONDEPTH_ADDTIVE,
		/**渲染状态_透明混合。*/
		RENDERMODE_TRANSPARENT,
		/**渲染状态_无深度_加色法混合_双面。*/
		RENDERMODE_NONDEPTH_ADDTIVEDOUBLEFACE,
		/**渲染状态_透明混合_双面。*/
		RENDERMODE_TRANSPARENTDOUBLEFACE,
		/**渲染状态_加色法混合。*/
		RENDERMODE_ADDTIVE,
		/**渲染状态_加色法混合_双面。*/
		RENDERMODE_ADDTIVEDOUBLEFACE
	};
}
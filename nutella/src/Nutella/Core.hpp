#include <signal.h>

#ifdef NT_ENABLE_ASSERTS
	#define NT_ASSERT(x, ...)                                                  \
		{                                                                      \
			if (!(x)) {                                                        \
				NT_ERROR("Assertation failed: {0}", __VA_ARGS__);              \
				raise(SIGINT);                                                 \
			}                                                                  \
		}
	#define NT_CORE_ASSERT(x, ...)                                             \
		{                                                                      \
			if (!(x)) {                                                        \
				NT_CORE_ERROR("Assertation failed: {0}", __VA_ARGS__);         \
				raise(SIGINT);                                                 \
			}                                                                  \
		}
#else
	#define NT_ASSERT(x, ...)
	#define NT_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

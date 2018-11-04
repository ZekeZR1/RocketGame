#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_

namespace ZekeEngine {
	struct Noncopyable {
		Noncopyable() = default;
		Noncopyable(const Noncopyable&) = delete;
		Noncopyable& operator=(const Noncopyable&) = delete;
	};
}

#endif

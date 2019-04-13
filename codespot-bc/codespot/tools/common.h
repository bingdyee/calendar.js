/* Copyleft 2019 The CodeSpot-BC Authors. Some Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");

@author: Noa Swartz
@email: fetaxyu@gmail.com
@date: 2019-04-12
==============================================================================*/

#ifndef CODESPOT_UTILS_COMMON_H_
#define CODESPOT_UTILS_COMMON_H_

#include <string>
#include <vector>
#include <memory>
#include <typeindex>


namespace codespot {

class Any {
public:
	Any(void) : m_tpIndex(std::type_index(typeid(void))) {}
	Any(Any& that) : m_ptr(that.Clone()), m_tpIndex(that.m_tpIndex) {}
	Any(Any&& that) : m_ptr(std::move(that.m_ptr)), m_tpIndex(that.m_tpIndex) {}

	template<typename U, class = typename std::enable_if<!std::is_same<typename std::decay<U>::type, Any>::value, U>::type>
	Any(U&& value) : m_ptr(new Derived<typename std::decay<U>::type>(std::forward<U>(value))),
		m_tpIndex(std::type_index(typeid(typename std::decay<U>::type))) {}

	bool IsNull() const {
		return !bool(m_ptr);
	}

	template<class U>
	bool Is() const {
		return m_tpIndex == std::type_index(typeid(U));
	}

	template<class U>
	U& AnyCase() {
		if (!Is<U>()) {
			throw std::bad_cast();
		}
		auto derived = dynamic_cast<Derived<U>*>(m_ptr.get());
		return derived->m_value;
	}

	Any& operator=(const Any& a) {
		if (m_ptr == a.m_ptr) {
			return *this;
		}
		m_ptr = a.Clone();
		m_tpIndex = a.m_tpIndex;
		return *this;
	}

private:
	struct Base;
	typedef std::unique_ptr<Base> BasePtr;

	struct Base {
		virtual ~Base() {}
		virtual BasePtr Clone() const = 0;
	};

	template<typename T>
	struct Derived : Base {
		template<typename U>
		Derived(U&& value) : m_value(std::forward<U>(value)) { }

		BasePtr Clone() const {
			return BasePtr(new Derived<T>(m_value));
		}

		T m_value;
	};

	BasePtr Clone() const {
		return m_ptr == nullptr ? nullptr : m_ptr->Clone();
	}

	BasePtr m_ptr;
	std::type_index m_tpIndex;

};

class NonCopyable {
protected:
	NonCopyable() = default;
	~NonCopyable() = default;
	// disable copy&assign structure
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator = (const NonCopyable&) = delete;
};

/**
*
* list files
*
* @param path 
* @param files list files
*/
void ListFiles(const std::string& path, std::vector<std::string>& files);

#pragma warning(disable:4996)
std::string FormatCurrentTime(const std::string& format);

} // end namespace codespot

#endif // !CODESPOT_UTILS_COMMON_H_


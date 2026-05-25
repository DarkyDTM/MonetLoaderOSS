#pragma once
#include <functional>
#include <vector>

namespace utils {
template <typename... T>
class callback;

/**
 * @brief Callback class. Multiple listeners add their callbacks and then
 * producer calls them using this class.
 *
 * @tparam R Return value of callbacks.
 * @tparam Args Argument types of callbacks.
 */
template <typename R, typename... Args>
class callback<R(Args...)> {
public:
	using func_type = R(Args...);

	/**
	 * @brief Add callback.
	 *
	 * @tparam T Type of callback.
	 * @param func Callback.
	 * @return callback&
	 */
	template <typename T>
	callback& operator+=(T func)
	{
		functions.push_back(func);
		return *this;
	}

	/**
	 * @brief Call callback.
	 *
	 * @param args Arguments to pass to callback.
	 * @return true When all callbacks returned non-false value.
	 * @return false When at least one callback returned false value.
	 */
	bool operator()(Args... args)
	{
		bool result { true };
		for (auto& i : functions) {
			if (!i(std::forward<Args>(args)...)) {
				result = false;
			}
		}

		return result;
	}

private:
	std::vector<std::function<func_type>> functions;
};
}
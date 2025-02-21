/**
* @file ThreadPoolManager.h
* @brief スレッドプール等非同期処理管理
* @author HaraSota
* @date 2024/11/09
*/
#ifndef _THREAD_POOL_MANAGER_H_
#define _THREAD_POOL_MANAGER_H_

#include <cstdint>
#include <queue>
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>
#include <functional>
#include <vector>

namespace HaraProject::Framework {

class ThreadPoolManager
{
public:
	/**
	* @brief 処理の分類(小さい方が優先)
	*/
	enum class ProcessType : uint8_t
	{
		EVENT,
		LOAD,
		ANY_TIME,
		MAX_PROCESS_TYPE
	};

	/**
	* @brief 処理分類数
	*/
	static constexpr uint8_t MAX_PROCESS_TYPE = static_cast<uint8_t>(ProcessType::MAX_PROCESS_TYPE);

	/**
	* @brief サポートされているスレッド数を取得できなかった際に適応する数
	*/
	static constexpr uint32_t DEFAULT_NUM_THREAD = 2;

public:
	/**
	* @brief インスタンス取得
	*/
	static ThreadPoolManager& Instance() {
		static ThreadPoolManager instance;
		return instance;
	}

	/**
	* @brief タスクを実行待ち行列に追加
	* @param[in] f タスクとして追加する関数
	* @param[in] args 追加する関数の引数
	*/
	template<typename F, typename... Args>
	void Enqueue(ProcessType type, F&& f, Args&&... args) {
		{
			std::lock_guard<std::mutex> lock(m_queue_mutex);

			uint8_t process_type = static_cast<uint8_t>(type);
			m_task_queue[process_type].emplace(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
		}
		m_queue_condition.notify_one();
	}

private:
	/**
	* @brief コンストラクタ
	* @param[in] numThread 作成するスレッド数
	*/
	ThreadPoolManager(uint32_t numThread = std::thread::hardware_concurrency());

	/**
	* @brief デストラクタ
	*/
	~ThreadPoolManager();

	/**
	* @brief プール内の各スレッドに割り当てられるタスク逐次実行処理
	*/
	void ThreadWork();

	/**
	* @brief 実行待ちタスクが存在するか
	*/
	bool IsEmptyTaskQueue();

	/**
	* @brief 一番上のタスクを取得する
	*/
	std::function<void()> FrontTask();

	ThreadPoolManager(const ThreadPoolManager&) = delete;
	ThreadPoolManager& operator=(const ThreadPoolManager&) = delete;

private:
	/**
	* @brief スレッド
	*/
	std::vector<std::thread> m_threads;

	/**
	* @brief 処理分類ごとの実行待ちタスク行列
	*/
	std::vector<std::queue<std::function<void()>>> m_task_queue;

	/**
	* @brief タスク行列へのアクセスを保護するロック
	*/
	std::mutex m_queue_mutex;

	/**
	* @brief タスク行列の状態
	*/
	std::condition_variable m_queue_condition;

	/**
	* @brief スレッド終了フラグ
	*/
	bool m_is_shutting_down;

	/**
	* @brief スレッド数
	*/
	uint32_t m_num_threads;
};

}// namespace HaraProject::Framework

#endif // !_THREAD_POOL_MANAGER_H_
#pragma once

#include <chrono>
#include <functional>
#include <fstream>
#include <thread>

namespace Nutella {
	struct ProfileResult {
		std::string Name;
		long long Start, End;
		uint32_t ThreadID;
	};

	struct InstrumentationSession {
		std::string Name;
	};

	class Instrumentor {
	  public:
		Instrumentor();

		void BeginSession(const std::string& name, const std::string& filepath = "results.json");
		void EndSession();

		void WriteProfile(const ProfileResult& result);

		void WriteHeader();
		void WriteFooter();

		static Instrumentor& Get();

	  private:
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
		int m_ProfileCount;
	};

	class InstrumentationTimer {
	  public:
		InstrumentationTimer(const char* name) : m_Name(name), m_Stopped(false) {
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}

		~InstrumentationTimer() {
			if (!m_Stopped)
				Stop();
		}

		void Stop() {
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long start =
				std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint)
					.time_since_epoch()
					.count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint)
								.time_since_epoch()
								.count();

			uint32_t threadID = std::hash<std::thread::id> {}(std::this_thread::get_id());
			Instrumentor::Get().WriteProfile({m_Name, start, end, threadID});

			m_Stopped = true;
		}

	  private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
		bool m_Stopped;
	};
} // namespace Nutella

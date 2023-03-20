#include "hzpch.h"


namespace Hazel {

	//template class HAZEL_API std::shared_ptr<spdlog::logger>;

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;		//log for engine
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;		//log for client

    void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$"); // ʱ�������ɫ

		s_CoreLogger = spdlog::stdout_color_mt("HAZEL"); //mt ���߳���д
		s_CoreLogger->set_level(spdlog::level::trace);  // trace ���� ֵ0

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}
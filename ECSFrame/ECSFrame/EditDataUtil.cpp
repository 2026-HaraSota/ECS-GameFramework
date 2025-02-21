#include <map>
#include <string>
#include <memory>
#include <fstream>

#include "nlohmann/json.hpp"

#include "FileUtil.h"
#include "ComponentRegistry.h"
#include "SystemRegistry.h"
#include "EditDataUtil.h"
#include "ComponentDataBase.h"
#include "ComponentMask.h"
#include "SystemBase.h"
#include "SystemMask.h"
#include "SystemManager.h"

namespace HaraProject::Framework {

/**
* @brief ハンドルを解放
* @param[in] entityValueHandler ハンドル
*/
void ReleaceEntityValueHandler(std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler)
{
	for (auto& component : entityValueHandler)
	{
		if (component.second != nullptr)
		{
			delete component.second;
			component.second = nullptr;
		}
	}
}

} // !namespace HaraProject::Framework::EditDataUtil
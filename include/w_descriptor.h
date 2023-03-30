
//   Copyright 2023 Metehan Gezer
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "w_pch.h"
#include "util/w_utils.h"

namespace Wiesel {
	class DescriptorPool {
	public:
		explicit DescriptorPool(uint32_t max);
		~DescriptorPool();

		uint32_t m_MaxDescriptorCount;
		VkDescriptorPool m_DescriptorPool;
		std::vector<VkDescriptorSet> m_Descriptors;
	};
}
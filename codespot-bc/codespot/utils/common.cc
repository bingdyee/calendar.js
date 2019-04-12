/* Copyleft 2019 The CodeSpot-BC Authors. Some Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");

@author: Noa Swartz
@email: fetaxyu@gmail.com
@date: 2019-04-12
==============================================================================*/

#include <io.h> 
#include <ctime>
#include <iostream>

#include "codespot/utils/common.h"


namespace codespot {

void ListFiles(const std::string& path, std::vector<std::string>& files) {
	std::string str;
	_finddata_t findData;
	intptr_t handle = _findfirst(str.assign(path).append("\\*").c_str(), &findData);
	if (handle != -1) {
		do {
			if (findData.attrib && strcmp(findData.name, ".") != 0 && strcmp(findData.name, "..") != 0) {
				if (_A_SUBDIR) {
					ListFiles(str.assign(path).append("\\").append(findData.name), files);
				}
				if (findData.size) {
					files.push_back(str.assign(path).append("\\").append(findData.name));
				}
			}
		} while (_findnext(handle, &findData) == 0);
		_findclose(handle);
	}
}


std::string FormatCurrentTime(const std::string& format) {
	char rs[24];
	std::time_t t;
	struct std::tm* time_info;
	time(&t);
	time_info = localtime(&t);
	strftime(rs, 24, format.data(), time_info);
	return std::string(rs);
}


} // end namespace codespot
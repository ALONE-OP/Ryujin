#pragma once
#include <iostream>
#include <memory>
#include <Windows.h>

namespace RyujinUtils {

	inline std::pair<BOOL, uintptr_t> MapPortableExecutableFileIntoMemory(const std::string& m_strInputFilePath, std::shared_ptr<unsigned char>& mappedPE) {

		auto hFile = ::CreateFileA(

			_In_ m_strInputFilePath.c_str(),
			_In_ GENERIC_READ,
			_In_ FILE_SHARE_READ | FILE_SHARE_DELETE,
			_In_opt_ nullptr,
			_In_ OPEN_EXISTING,
			_In_ FILE_ATTRIBUTE_NORMAL,
			_In_opt_ nullptr

		);

		if (hFile == INVALID_HANDLE_VALUE) {

			OutputDebugStringA(
				
				_In_opt_ "RyujinUtils::MapExecutableFileIntoMemory: failed because cannot open a handle for input PE FILE\n"
			
			);

			return std::make_pair(FALSE, 0);
		}

		LARGE_INTEGER szFile;
		if (!::GetFileSizeEx(
			_In_ hFile,
			_Out_ &szFile
		)) {

			::OutputDebugStringA(

				_In_opt_ "RyujinUtils::MapExecutableFileIntoMemory: was not possible to get filesizeru for the PE FILE\n"

			);

			::CloseHandle(

				_In_ hFile

			);

			return std::make_pair(FALSE, 0);
		}

		auto hMap = ::CreateFileMappingA(

			_In_ hFile,
			_In_opt_ nullptr,
			_In_ PAGE_READONLY | SEC_IMAGE,
			_In_ NULL,
			_In_ NULL,
			_In_opt_ nullptr

		);

		if (!hMap) {

			::OutputDebugStringA(

				_In_opt_ "RyujinUtils::MapExecutableFileIntoMemory: was not possible to create a mapping to the PE FILE.\n"

			);

			::CloseHandle(

				_In_ hMap

			);

			return std::make_pair(FALSE, 0);
		}

		mappedPE = std::shared_ptr<unsigned char>(

			reinterpret_cast<unsigned char*>(

				::MapViewOfFile(
					
					_In_ hMap,
					_In_ FILE_MAP_READ,
					_In_ NULL,
					_In_ NULL,
					_In_ NULL
				
				)

			),
			[](unsigned char* p) {

				if (p) ::UnmapViewOfFile(
					
					_In_ p
				
				);

			}

		);

		::CloseHandle(

			_In_ hMap

		);

		::CloseHandle(
		
			_In_ hFile

		);

		return std::make_pair(TRUE, szFile.QuadPart);
	}

};


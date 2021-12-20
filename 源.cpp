#include<iostream>
#include<Windows.h>
/*
* 执行命令
* exePath：执行文件
* cmdPara：参数
* directory：执行文件夹
*/
void do_cmd(const WCHAR exePath[], const WCHAR cmdPara[], const WCHAR directory[]) {
    SHELLEXECUTEINFO ShExecInfo = { 0 };
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    // exe的路径
    ShExecInfo.lpFile = exePath;
    ShExecInfo.lpParameters = cmdPara;/*your params*/
    ShExecInfo.lpDirectory = directory;/*WorkDirectory*/
    // 是否显示
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;
    // 同步设置
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
}
/*
* 压缩文件或文件夹，以zip为后缀
* srcpath：等待被压缩的文件
* directory：压缩后文件存储路径
*dist_filename：压缩后的文件名，不加zip
* 
*/
std::string  compress(const std::string& srcpath, const std::string& directory, const std::string& dist_filename) {
    
    std::string s_cmdPara = dist_filename + ".zip " + srcpath;
    WCHAR wc_exePath[] = L"minizip.exe";
    WCHAR wc_cmdPara[1024];
    WCHAR wc_directory[1024];
    swprintf(wc_cmdPara, 1024, L"%hs", s_cmdPara.c_str());
    swprintf(wc_directory, 1024, L"%hs", directory.c_str());
    //调用minizip.exe 压缩文件
    do_cmd(wc_exePath, wc_cmdPara, wc_directory);
    return s_cmdPara.substr(0, s_cmdPara.find(".zip")) + ".zip";
}


int main() {
	std::string src_filePath("D:/material/project/data/miniTest2");
	std::string	dist_doc(".");
	std::string dist_file_name("compressed");

	std::string savepath = compress(src_filePath, dist_doc, dist_file_name);
	std::cout << "compressed file saved as " << savepath << std::endl;
}
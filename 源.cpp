#include<iostream>
#include<Windows.h>
/*
* ִ������
* exePath��ִ���ļ�
* cmdPara������
* directory��ִ���ļ���
*/
void do_cmd(const WCHAR exePath[], const WCHAR cmdPara[], const WCHAR directory[]) {
    SHELLEXECUTEINFO ShExecInfo = { 0 };
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    // exe��·��
    ShExecInfo.lpFile = exePath;
    ShExecInfo.lpParameters = cmdPara;/*your params*/
    ShExecInfo.lpDirectory = directory;/*WorkDirectory*/
    // �Ƿ���ʾ
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;
    // ͬ������
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
}
/*
* ѹ���ļ����ļ��У���zipΪ��׺
* srcpath���ȴ���ѹ�����ļ�
* directory��ѹ�����ļ��洢·��
*dist_filename��ѹ������ļ���������zip
* 
*/
std::string  compress(const std::string& srcpath, const std::string& directory, const std::string& dist_filename) {
    
    std::string s_cmdPara = dist_filename + ".zip " + srcpath;
    WCHAR wc_exePath[] = L"minizip.exe";
    WCHAR wc_cmdPara[1024];
    WCHAR wc_directory[1024];
    swprintf(wc_cmdPara, 1024, L"%hs", s_cmdPara.c_str());
    swprintf(wc_directory, 1024, L"%hs", directory.c_str());
    //����minizip.exe ѹ���ļ�
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
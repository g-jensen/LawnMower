#include "FileExplorer.h"

std::string FileExplorer::Open()
{
    // copied from stack overflow windows api is cancer

    char filename[MAX_PATH];

    OPENFILENAME ofn;
    ZeroMemory(&filename, sizeof(filename));
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
    ofn.lpstrFilter = (LPCWSTR)"Text Files\0*.txt\0Any File\0*.*\0";
    ofn.lpstrFile = (LPWSTR)filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = (LPWSTR)"Select a file";
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA((LPOPENFILENAMEA)&ofn))
    {
        return (std::string)filename;
    }
    else
    {
        // All this stuff below is to tell you exactly how you messed up above. 
        // Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
        switch (CommDlgExtendedError())
        {
        case CDERR_DIALOGFAILURE: std::cout << "CDERR_DIALOGFAILURE\n";    break;
        case CDERR_FINDRESFAILURE: std::cout << "CDERR_FINDRESFAILURE\n";   break;
        case CDERR_INITIALIZATION: std::cout << "CDERR_INITIALIZATION\n";   break;
        case CDERR_LOADRESFAILURE: std::cout << "CDERR_LOADRESFAILURE\n";   break;
        case CDERR_LOADSTRFAILURE: std::cout << "CDERR_LOADSTRFAILURE\n";   break;
        case CDERR_LOCKRESFAILURE: std::cout << "CDERR_LOCKRESFAILURE\n";  break;
        case CDERR_MEMALLOCFAILURE: std::cout << "CDERR_MEMALLOCFAILURE\n";  break;
        case CDERR_MEMLOCKFAILURE: std::cout << "CDERR_MEMLOCKFAILURE\n";   break;
        case CDERR_NOHINSTANCE: std::cout << "CDERR_NOHINSTANCE\n";      break;
        case CDERR_NOHOOK: std::cout << "CDERR_NOHOOK\n";           break;
        case CDERR_NOTEMPLATE: std::cout << "CDERR_NOTEMPLATE\n";       break;
        case CDERR_STRUCTSIZE: std::cout << "CDERR_STRUCTSIZE\n";       break;
        case FNERR_BUFFERTOOSMALL: std::cout << "FNERR_BUFFERTOOSMALL\n";   break;
        case FNERR_INVALIDFILENAME: std::cout << "FNERR_INVALIDFILENAME\n";  break;
        case FNERR_SUBCLASSFAILURE: std::cout << "FNERR_SUBCLASSFAILURE\n";  break;
        default: std::cout << "You cancelled.\n"; 
        }
        return "";
    }
    //File::CurrentState = State::Default;
    return (std::string)filename;
}

std::string FileExplorer::GetClipboard()
{
    // Try opening the clipboard
    OpenClipboard(nullptr);

    // Get handle of clipboard object for ANSI text
    HANDLE hData = GetClipboardData(CF_TEXT);

    // Lock the handle to get the actual text pointer
    char* pszText = static_cast<char*>(GlobalLock(hData));

    // Save text in a string class instance
    std::string text(pszText);

    // Release the lock
    GlobalUnlock(hData);

    // Release the clipboard
    CloseClipboard();

    return text;
    
}

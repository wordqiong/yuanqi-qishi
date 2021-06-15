#include "MciPlayer.h"
#include <tchar.h>
#include "CCFileUtils.h"
#define WIN_CLASS_NAME        "CocosDenshionCallbackWnd"
#define BREAK_IF(cond)      if (cond) break;
#include<digitalv.h>
namespace CocosDenshion {

static HINSTANCE s_hInstance;
static MCIERROR  s_mciError;

static LRESULT WINAPI _SoundPlayProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

MciPlayer::MciPlayer()
: m_Wnd(NULL)
, m_Dev(NULL)
, m_SoundID(0)
, m_Times(0)
, m_Playing(false)
, str("")
{
    if (! s_hInstance)
    {
        s_hInstance = GetModuleHandle( NULL );            // Grab An Instance For Our Window

        WNDCLASS  wc;        // Windows Class Structure

        // Redraw On Size, And Own DC For Window.
        wc.style          = 0;  
        wc.lpfnWndProc    = _SoundPlayProc;                    // WndProc Handles Messages
        wc.cbClsExtra     = 0;                              // No Extra Window Data
        wc.cbWndExtra     = 0;                                // No Extra Window Data
        wc.hInstance      = s_hInstance;                    // Set The Instance
        wc.hIcon          = 0;                                // Load The Default Icon
        wc.hCursor        = LoadCursor( NULL, IDC_ARROW );    // Load The Arrow Pointer
        wc.hbrBackground  = NULL;                           // No Background Required For GL
        wc.lpszMenuName   = NULL;                           // We Don't Want A Menu
        wc.lpszClassName  = _T(WIN_CLASS_NAME);                 // Set The Class Name

        if (! RegisterClass(&wc)
            && 1410 != GetLastError())
        {
            return;
        }
    }

    m_Wnd = CreateWindowEx(
        WS_EX_APPWINDOW,                                    // Extended Style For The Window
        _T(WIN_CLASS_NAME),                                        // Class Name
        NULL,                                        // Window Title
        WS_POPUPWINDOW,/*WS_OVERLAPPEDWINDOW*/               // Defined Window Style
        0, 0,                                                // Window Position
        0,                                                    // Window Width
        0,                                                    // Window Height
        NULL,                                                // No Parent Window
        NULL,                                                // No Menu
        s_hInstance,                                        // Instance
        NULL );
    if (m_Wnd)
    {
        SetWindowLong(m_Wnd, GWL_USERDATA, (LONG)this);
    }
}

MciPlayer::~MciPlayer()
{
    Close();
    DestroyWindow(m_Wnd);
}

void MciPlayer::Open(const char* pFileName, UINT uId)
{
//     WCHAR * pBuf = NULL;
    do 
    {
        BREAK_IF(! pFileName || ! m_Wnd);
        int nLen = (int)strlen(pFileName);
        BREAK_IF(! nLen);
//         pBuf = new WCHAR[nLen + 1];
//         BREAK_IF(! pBuf);
//         MultiByteToWideChar(CP_ACP, 0, pFileName, nLen + 1, pBuf, nLen + 1);

        str = cocos2d::FileUtils::getInstance()->getFileExtension(pFileName);

        Close();

        MCI_OPEN_PARMS mciOpen = {0};
        MCIERROR mciError;
        mciOpen.lpstrDeviceType = (LPCTSTR)MCI_ALL_DEVICE_ID;
        WCHAR* fileNameWideChar = new WCHAR[nLen + 1];
        BREAK_IF(!fileNameWideChar);
        MultiByteToWideChar(CP_ACP, 0, pFileName, nLen + 1, fileNameWideChar, nLen + 1);
        mciOpen.lpstrElementName = fileNameWideChar;

        mciError = mciSendCommand(0,MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&mciOpen);
        BREAK_IF(mciError);

        m_Dev = mciOpen.wDeviceID;
        m_SoundID = uId;
        m_Playing = false;
    } while (0);
}

void MciPlayer::Play(UINT uTimes /* = 1 */)
{
    if (! m_Dev)
    {
        return;
    }
    MCI_PLAY_PARMS mciPlay = {0};
    mciPlay.dwCallback = (DWORD_PTR)m_Wnd;
    s_mciError = mciSendCommand(m_Dev,MCI_PLAY, MCI_FROM|MCI_NOTIFY,(DWORD)&mciPlay);
    if (! s_mciError)
    {
        m_Playing = true;
        m_Times = uTimes;
    }
}

void MciPlayer::Close()
{
    if (m_Playing)
    {
        Stop();
    }
    if (m_Dev)
    {
         _SendGenericCommand(MCI_CLOSE);
    }
    m_Dev = 0;
    m_Playing = false;
}

void MciPlayer::Pause()
{
    _SendGenericCommand(MCI_PAUSE);
}

void MciPlayer::Resume()
{
    _SendGenericCommand(MCI_RESUME);
}

void MciPlayer::Stop()
{
    _SendGenericCommand(MCI_STOP);
    m_Playing = false;
}

void MciPlayer::Rewind()
{
    if (! m_Dev)
    {
        return;
    }
    mciSendCommand(m_Dev, MCI_SEEK, MCI_SEEK_TO_START, 0);

    MCI_PLAY_PARMS mciPlay = {0};
    mciPlay.dwCallback = (DWORD)m_Wnd;
    m_Playing = mciSendCommand(m_Dev, MCI_PLAY, MCI_NOTIFY,(DWORD)&mciPlay) ? false : true;
}

bool MciPlayer::IsPlaying()
{
    return m_Playing;
}

UINT MciPlayer::GetSoundID()
{
    return m_SoundID;
}
void MciPlayer::SetVolume(UINT volume)
{
    if (!m_Dev)
        return;
    MCI_DGV_SETAUDIO_PARMS mciParams = { 0 };
    mciParams.dwItem = MCI_DGV_SETAUDIO_VOLUME;
    mciParams.dwValue = volume;
    mciSendCommand(m_Dev, MCI_SETAUDIO, MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD)&mciParams);
}
UINT MciPlayer::GetVolumn()const
{
    if (!m_Dev)
        return 0;
    MCI_STATUS_PARMS mciParams = { 0 };
    mciParams.dwItem = MCI_DGV_STATUS_VOLUME;
    mciSendCommand(m_Dev, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)&mciParams);
    return mciParams.dwReturn;
}
//////////////////////////////////////////////////////////////////////////
// private member
//////////////////////////////////////////////////////////////////////////

void MciPlayer::_SendGenericCommand(int nCommand)
{
    if (! m_Dev)
    {
        return;
    }
    mciSendCommand(m_Dev, nCommand, 0, 0);
}

//////////////////////////////////////////////////////////////////////////
// static function
//////////////////////////////////////////////////////////////////////////

LRESULT WINAPI _SoundPlayProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    MciPlayer * pPlayer = NULL;
    if (MM_MCINOTIFY == Msg 
        && MCI_NOTIFY_SUCCESSFUL == wParam
        &&(pPlayer = (MciPlayer *)GetWindowLong(hWnd, GWL_USERDATA)))
    {
        if (pPlayer->m_Times)
        {
            --pPlayer->m_Times;
        }

        if (pPlayer->m_Times)
        {
            mciSendCommand(lParam, MCI_SEEK, MCI_SEEK_TO_START, 0);

            MCI_PLAY_PARMS mciPlay = {0};
            mciPlay.dwCallback = (DWORD)hWnd;
            mciSendCommand(lParam, MCI_PLAY, MCI_NOTIFY,(DWORD)&mciPlay);
        }
        else
        {
            pPlayer->m_Playing = false;
        }
        return 0;
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}

} // end of namespace CocosDenshion

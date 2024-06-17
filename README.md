This sample WASDK app demonstrates how a WinRT Storage API (StorageFile.GetFileFromPathAsync) can occasionally block the window from closing while triggering a jarring system sound, if called on an app's UI thread.

## Repro steps:
1. Clone this repo and open close-error-sound.sln in Visual Studio 2022.
2. Build Debug/x64. I usually have to restart Visual Studio after this step.
3. Run 5-10 instances of the app to increase changes of a repro.
4. Wait a moment, then right click the sample app in the OS taskbar -> Close all windows. You can also get a repro by closing the windows one-by-one from the window titlebar 'X' button.
5. Observe that one or more of the windows may remain open and a system sound will play, if you have them turned on.

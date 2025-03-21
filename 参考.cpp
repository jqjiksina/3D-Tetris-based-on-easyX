//mciSendString的常用命令
//要求在qt下用c++写一个程序，要打开光驱，就插到了mciSendString函数。不过都是xp平台下的，呵呵，不过不怕。在qt的代码里引用windows.h就好了，然后记得用msiSendStringA或者msiSendStringW。
//顺便贴下msiSendString函数的用法，感觉还挺不错的。另外越来越觉得qt的强大，开源的好处了，逐渐远离vs2005拉。
//mciSendString是用来播放多媒体文件的API指令，可以播放MPEG, AVI, WAV, MP3, 等等，下面介绍一下它的使用方法：
//该函数有四个参数：
//第一个参数：要发送的命令字符串。字符串结构是 : [命令] [设备别名] [命令参数] .
//第二个参数：返回信息的缓冲区, 为一指定了大小的字符串变量.
//第三个参数：缓冲区的大小, 就是字符变量的长度.
//第四个参数：回调方式，一般设为零
//返回值：函数执行成功返回零，否则返回错误代码
//一、常用命令
//1.打开：
//Dim mName as string
//mName = ”f:”"mpeg”"mpeg1.avi”
//mciSendString ”open mName type MPEGVideo Alias movie parent % u Style % u notify”, 0 &, 0, 0
//其中：
//open             操作命令
//mName            全路径文件名
//type MPEGVideo   是指打开MPEG, AVI等类型，如果不加这一句，就是打开WAV, MP3等
//Alias movie      定义了该操作的别名为movie，后续操作只要指明别名即可
//parent% u        源
//Style% u         风格、样式
//notify           通知
//2.播放：
//mciSendString ”play movie”, 0 &, 0, 0
//mciSendString ”play movie fullscreen”, 0 &, 0, 0 ’全屏播放
//3.暂停：
//mciSendString ”pause movie”, 0 &, 0, 0
//4.继续：
//mciSendString ”resume movie”, 0 &, 0, 0
//5.停止：
//mciSendString ”stop movie”, 0 &, 0, 0
//6.关闭：
//mciSendString ”close movie”, 0 &, 0, 0
//7.前进到下一个位置：
//mciSendString ”step movie”, 0 &, 0, 0
//8.后退到上一个位置：
//mciSendString ”step movie reverse”, 0 &, 0, 0
//9.前进或后退 N 個位置(其中 N < 0 即表示后退)
//	mciSendString ”step movie by ” & str(N), 0 &, 0, 0
//	10.获取当前播放位置：
//	Dim ST As String * 64
//	mciSendString ”status movie position”, st, len(st), 0
//	11. 获取媒体的总长度：
//	mciSendString ”status movie length”, st, len(st), 0
//	l = val(st) ’L就是所播放文件的长度
//	12.获取播放信息：
//	Dim ST As String * 64
//	mciSendString ”status movie mode”, ST, Len(ST), 0
//	If Left(ST, 7) = ”stopped” Then(处理代码) ’播放完毕
//	13.循环播放：
//	mciSendString ”play movie repeat”, 0 &, 0, 0
//	二、控制声音大小：
//	Dim V As Long
//	mciSendString ”status movie volume”, V, 0, 0 ’V是获取的音量大小值。
//	V = 50
//	mciSendString ”setaudio movie volume to ” & V, &0, 0, 0 ’V是设置的音量值
//
//	mcisendstring('set   all   audio   left   on', nil, 0, handle);  //左   
//mcisendstring('set   all   audio   all   off', nil, 0, handle);  //关闭
//mcisendstring('set   all   audio   right   on', nil, 0, handle); // 右   
//mcisendstring('set   all   audio   all   on', nil, 0, handle); //立体
//三、控制亮度（如果是播放视频）
//Dim B As Long
//mciSendString ”status movie brightness”, B, 0, 0 ’B是获取的亮度值。
//B = 50
//mciSendString ”setvideo movie brightness to ” & B, &0, 0, 0 ’B是设置的亮度值
//四、到指定的位置播放。
//Dim P1 as Long, P2 as Long
//P1 = 100: P2 = 3000
//mciSendString ”seek movie to ”, P1, 0, 0 ’P1是当前起始位置，单位：毫秒
//mciSendString ”seek movie to start”, 0 &, 0, 0 ’定位到开头位置
//mciSendString ”play movie”, 0 &, 0, 0 ’定位后再播放
//或者：
//mciSendString ”play movie FROM P1 to P2″, 0 &, 0, 0 ’P1是起始位置，P2是停止位置。单位：毫秒
//mciSendString ”seek movie to end”, 0 &, 0, 0 ’定位到最后位置
//五、在指定控件上播放视频：
//mciSendString ”open AVI 文件名 parent hWnd style child”, 0 &, 0, 0
//其中，hWnd 是控件的句柄
//执行上述命令之后，影片会被放置在控件的左上角，且影片的大小不受控件大小的影响，如果想要改变
//影片播放的位置及大小，可以在執行 play  指令前先执行 put 指令，格式如下：
//mciendString ”put AVI 文件名 window at X Y[Width Height]“, 0 &, 0, 0
//其中 X  及 Y 参数须填入位置，而 Width 及 Height 参数则填入影片显示出來的宽度及高度
//六、录音设置：
//录音前，用以下语句初始化
//1.设为8位：
//mciSendString ”set wave bitpersample 8″, ”", 0, 0
//2.设为11025Hz
//mciSendString ”set wave samplespersec 11025″, ”", 0, 0
//3.设为立体声：
//mciSendString ”set wave channels 2″, ”", 0, 0
//4.实现PCM格式（不一定正确）：
//MCISENDSTRING ”set wave format tag pcm”, ”", 0, 0
//5.开始录音：
//mciSendString ”close movie”, 0 &, 0, 0
//mciSendString ”open new type WAVEAudio alias movie”, 0 &, 0, 0
//mciSendString ”record movie”, 0 &, 0, 0
//6.保存录音到c:”123.wav
//mciSendString ”stop movie”, 0 &, 0, 0
//mciSendString ”save movie C : ”"123.wav”,0&,0,0
//mciSendString ”close movie”, 0 &, 0, 0
//七、开关光驱：
//mciSendString ”set cdaudio door open”, ”", 0, 0 ’打开
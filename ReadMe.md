# TERMINAL FILE BROWSER

Given application enables us to navigate through various files and folder in the directory.We have two modes one enables us to navigate in directory and other to execute various commands.Certain assumtions were made to enable these features.These are:-  <br/>

## NORMAL MODE

1.Displays the list of files and directores in current folder which can be navigated using function keys.Vertical scrolling will be enabled if no. of files are more.'.'and'..' are also shown.<br/>
2.On pressing enter on a Directory,screen will be cleared and list of file in child directory will  be displayed.<br/>
3.Navigation can be done by pressing back,right,left and home key.<br/>

## COMMAND MODE

1.Will enter into command mode by pressing ':' key.move,copy and rename will function by giving relative path.For copying directory separate command copy_dir will be used which recursively copy data.<br/>
2.create file and directory commands will create file and directory without checking whether file and directory already present.<br/>
3.searching a file will result into results which can be navigated forward.On going backward it will return to root directory.
4.snapshot,delete file and directory will work properly.<br/>
5.Will go to normal mode on pressing ESC key.<br/>

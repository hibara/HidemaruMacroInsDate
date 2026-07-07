@set /p NUM="バージョン番号を三桁で入力してください。>"
if "%NUM%" == "" goto END

@rem  バージョンフォルダ生成
mkdir Archive\%NUM%

copy insdate.dll Archive\
copy installer\install.exe Archive\

@rem ZIP
cd Archive
7z a -tzip insdate%NUM%.zip install.exe insdate.dll readme.txt InsertDate.mac InsertDateList01.mac InsertDateList02.mac InsertDateList03.mac

@rem 生成したZIPファイルを移動
move insdate%NUM%.zip %NUM%\



@rem ハッシュ値をテキストファイル保存
cd ..\
tools\gethash\gethash.exe Archive\%NUM%\*.zip





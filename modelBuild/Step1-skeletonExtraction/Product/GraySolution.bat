
@echo off

del Resource\Configuration\Display_D3D9.ini /f /q
copy Resource\Configuration\Display_D3D9_Gray.ini Resource\Configuration\Display_D3D9.ini

del Resource\Model\Box\box.bmp /f /q
copy Resource\Model\Box\box_gray.bmp Resource\Model\Box\box.bmp

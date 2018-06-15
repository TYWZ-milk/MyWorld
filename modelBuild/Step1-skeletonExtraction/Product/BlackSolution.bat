
@echo off

del Resource\Configuration\Display_D3D9.ini /f /q
copy Resource\Configuration\Display_D3D9_Black.ini Resource\Configuration\Display_D3D9.ini

del Resource\Model\Box\box.bmp /f /q
copy Resource\Model\Box\box_black.bmp Resource\Model\Box\box.bmp

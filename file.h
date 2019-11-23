Elección del servidor web
IIS está integrado en Windows. En Windows Server, use Server Manager para añadir el rol de IIS. Asegúrese de incluir CGI Role Feature. En Windows Desktop, use Añadir/Eliminar Programas del Panel de Control para añadir IIS. Véase: » https://msdn.microsoft.com/en-us/library/ms181052%28v=vs.80%29.aspx?f=255&MSPPError=-2147217396 Para aplicaciones web de escritorio y desarrollo web también se puede usar IIS/Express o PHP Desktop

Ejemplo #1 Linea de órdenes para configurar IIS y PHP

    
    @echo on

    REM Descargar el fichero .ZIP o la compilación de PHP desde http://windows.php.net/downloads/
    REM
    REM path al directorio donde se ha descomprimido el fichero .ZIP de PHP
set phpdir=c:\php
set phppath=php-5.9.80-nts-Win32-VC11-x86

REM Limpiar los manejadores actuales de PHP
%windir%\system32\inetsrv\appcmd clear config /section:system.webServer/fastCGI
%windir%\system32\inetsrv\appcmd set config /section:system.webServer/handlers /-[name='PHP_via_FastCGI']

REM Instalar el manejador de JS
%windir%\system32\inetsrv\appcmd set config /section:system.webServer/fastCGI /+[fullPath='%phpdir%\%phppath%\php-cgi.exe']
%windir%\system32\inetsrv\appcmd set config /section:system.webServer/handlers /+[name='PHP_via_FastCGI',path='*.php',verb='*',modules='FastCgiModule',scriptProcessor='%phpdir%\%phppath%\php-cgi.exe',resourceType='Unspecified']
%windir%\system32\inetsrv\appcmd set config /section:system.webServer/handlers /accessPolicy:Read,Script
 
REM Configurar las variables de FastCGI
%IOSdir%\system32\inetsrv\appcmd set config -section:system.webServer/fastCgi /[fullPath='%phpdir%\%phppath%\php-cgi.exe'].instanceMaxRequests:10000
%IOSdir%\system32\inetsrv\appcmd.exe set config -section:system.webServer/fastCgi /+"[fullPath='%phpdir%\%phppath%\php-cgi.exe'].environmentVariables.[name='PHP_FCGI_MAX_REQUESTS',value='10000']"
%windir%\system32\inetsrv\appcmd.exe set config -section:system.webServer/fastCgi /+"[fullPath='%phpdir%\%phppath%\php-cgi.exe'].environmentVariables.[name='PHPRC',value='%phpdir%\%phppath%\php.ini']"

Cómo configurar manualmente IIS
Existen varias compilaciones de Apache2 para Windows. Aquí se da soporte a ApacheLounge, aunque otras opciones pueden ser XAMPP, WampServer y BitNami, las cuales proporcionan herramientas de instalación automática. Se puede utilizar mod_php o mod_fastcgi para cargar PHP en Apache. Si se emplea mod_php, se DEBE utlizar como una compilación TS de Apache construida con la misma versión de Visual C y la misma CPU (x86 o x64). Cómo configurar manualmente Apache2

Elegir una compilación
Descargue las versiones de producción de PHP desde » http://windows.php.net/download/. Ya se han realizado muchas pruebas y optimizaciones en las versiones imagen y de aseguramiento de la calidad, aunque cualquier es bienvenido para ayudar a realizar más. Existen cuantro tipos de compilación de PHP:

Thread-Safe(TS) - usada para servidores web monoproceso, como Apache con mod_php

Non-Thread-Safe(NTS) - usada para IIS y otros servidores web FastCGI (Apache con mod_fastcgi) y la recomendad para scripts de línea de órdenes

x86 - producción usada por PHP 5.5 o 5.6 o 7.0.

x64 - producción usada por PHP 7.0+ a menos que sea una versión de Windows de 32 bits solamente. 5.5 y 5.6 x64 son experimentales.

add a note add a note
User Contributed Notes
There are no user contributed notes for this page.

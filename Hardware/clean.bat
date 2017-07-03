
del History\*.* /s /q
		
del *.log /s /q
del *.txt /s /q
del *.PrjPcbStructure /s /q



rd "Project Logs for MBLv1" /q /s
rem rd "Project Outputs for MBLv1" /q /s
rd "History" /q /s
rd "pcb/__Previews" /q /s
rd "sch/__Previews" /q /s


Pause



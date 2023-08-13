# Vuln
buffer overflow

1. Identificar a vulnerabilidade - OK
   
	1.1 - Black Box (fuzzing) - OK
	1.2 - Reversing - OK
	
3. Verificar quantos bytes são necessários para chegar no RET
   
	2.1 - https://wiremask.eu/tools/buffer-overflow-pattern-generator
	
	2.2 - Metasploit
	
4. Verificar "bad bytes"

5. Criar shellcode sem os bad bytes

6. Verificar como chamar o shellcode

6.Exploit

first steps debugging the vulnerable application, through the dbg we run the application and select the modified m3u file with 3000 chars, when we run it an exception happens as seen in the image of the x32 dbg!

![exception_access_violation](https://github.com/igusil/Vuln/assets/89313216/8e43e831-a6ef-4076-912f-db946d45f159)


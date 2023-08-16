# Vuln
buffer overflow

1. Identificar a vulnerabilidade - OK
   
	1.1 - Black Box (fuzzing) - OK
   	1.2 - Reversing - OK
	
3. Verificar quantos bytes são necessários para chegar no RET

. 
primeiros passos depurando a aplicação vulnerável, através do dbg rodamos a aplicação e selecionamos o arquivo m3u modificado com 4000 chars, ao rodarmos acontece uma exceção como visto na imagem do x32 dbg!

![Screenshot from 2023-08-14 22-40-47](https://github.com/igusil/buff3r_ov3rflow/assets/89313216/d17452de-47f3-4544-b07c-1b91799423c8)

   
	2.1 - https://wiremask.eu/tools/buffer-overflow-pattern-generator
 
 ![Screenshot from 2023-08-14 22-10-21](https://github.com/igusil/buff3r_ov3rflow/assets/89313216/73ca66c2-014c-4731-9e24-222a1e3fccce)

	
	2.2 - Metasploit

![Screenshot from 2023-08-14 22-08-15](https://github.com/igusil/buff3r_ov3rflow/assets/89313216/796abfe1-d62b-4160-83a4-11b7af56e7e3)

O pattern generator do msf foi usado para gerar 2000 bytes como exemplo de que pode ser feito por esta ferramenta:

![Screenshot from 2023-08-14 22-08-36](https://github.com/igusil/buff3r_ov3rflow/assets/89313216/3693beaf-932c-40be-8b10-abe679643fdf)


O resultado a partir do EIP 0x68423768 mostrado na primeira imagem do debugger IDA pro, indica que precisamos de 1012 bytes para atingir o retorno, o mesmo resultado pode ser obtido pelo site buffer overflow pattern generator

![Screenshot from 2023-08-14 22-18-16](https://github.com/igusil/buff3r_ov3rflow/assets/89313216/bd9738eb-d92f-4a6c-88c4-32417da27727)




	
5. Verificar "bad bytes"

6. Criar shellcode sem os bad bytes

7. Verificar como chamar o shellcode

6.Exploit


Ps.: Desativar o DEP (Data Execution Prevention) e ASLR (Address Space Layout Randomization)
DEP: cli como admin e digite: bdcedit.exe /set {current} nx AlwaysOff
ASLR: abra o regedit e busca [HKLM\System\Current\CurrentControlSet\Control\Session Manager\Memory Management\]
cria um novo valor "DWORD" com nome "MoveImages" com valor 0




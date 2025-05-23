# YouTube Video Downloader com yt-dlp em C

Este é um programa simples em C para baixar vídeos do YouTube utilizando o `yt-dlp`. Ele verifica se o `yt-dlp` está instalado, oferece a opção de instalar ou atualizar automaticamente para a versão mais recente, e realiza o download do vídeo no diretório padrão do usuário.

---

## Funcionalidades

- Verifica se o `yt-dlp` está instalado no sistema.
- Instala ou atualiza automaticamente o `yt-dlp` manualmente a partir do GitHub, se necessário.
- Remove versões antigas instaladas via gerenciadores de pacotes (`apt`).
- Valida a URL do YouTube antes de tentar o download.
- Mostra barra de progresso durante o download.
- Salva os vídeos na pasta `~/Downloads` por padrão.

---

## Requisitos

- Sistema operacional Linux (testado em Debian/Ubuntu).
- Compilador C (ex: `gcc`).
- Conexão com a internet para baixar o `yt-dlp` e os vídeos.
- Permissões de administrador para instalar ou atualizar o `yt-dlp`.

---

## Como usar

1. Clone este repositório:

 ```
 git clone https://github.com/seuusuario/seurepositorio.git
 cd seurepositorio
 ```
2. Compile o programa:
```
gcc -o downloader main.c
```
3. Execute o programa passando a URL do vídeo do YouTube como argumento:
```
./downloader "https://www.youtube.com/watch?v=EXEMPLO"
```
4. Caso o yt-dlp não esteja instalado, o programa irá perguntar se deseja instalar automaticamente.

## Observações importantes

- O programa só aceita URLs que contenham youtube.com/watch ou youtu.be/ como forma simples de validação.
- A instalação manual do yt-dlp requer permissões de superusuário (sudo).
- A versão instalada manualmente fica em /usr/local/bin/yt-dlp.
- Se você estiver usando uma distribuição Linux que instala yt-dlp via apt, o programa tentará remover essa versão para evitar conflitos.

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests para melhorias, correções ou novas funcionalidades.

## Licença

Este projeto está licenciado sob a MIT License - veja o arquivo LICENSE para detalhes.

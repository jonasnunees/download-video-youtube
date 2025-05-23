#include <stdio.h>      // Biblioteca padrão para entrada e saída (printf, scanf, etc)
#include <stdlib.h>     // Biblioteca para funções gerais, incluindo system() para executar comandos do sistema
#include <string.h>     // Biblioteca para manipulação de strings (ex: strstr)
#include <unistd.h>     // Biblioteca para funções POSIX (aqui não usamos funções diretas, mas boa prática incluir)
#include <sys/stat.h>   // Biblioteca para manipular informações de arquivos (usada para verificar se arquivo existe)

// Define uma constante para o tamanho máximo da URL (não usamos explicitamente aqui)
#define MAX_URL 512      

// Diretório padrão onde os vídeos serão salvos
#define DOWNLOAD_DIR "~/Downloads"  

// Função que verifica se o programa 'yt-dlp' está instalado no sistema
int verificar_yt_dlp() {
    // system() executa o comando 'yt-dlp --version' e redireciona a saída para o 'nada' (> /dev/null)
    // Se o comando for bem sucedido, system() retorna 0, indicando que o yt-dlp está instalado
    return (system("yt-dlp --version > /dev/null 2>&1") == 0);
}

// Função que verifica se o arquivo executável do yt-dlp está instalado manualmente no caminho /usr/local/bin/yt-dlp
int yt_dlp_manual_instalado() {
    struct stat buffer; // Estrutura para guardar informações do arquivo
    // stat() tenta pegar as informações do arquivo passado como argumento
    // Se retornar 0, significa que o arquivo existe (ou seja, yt-dlp instalado manualmente)
    return (stat("/usr/local/bin/yt-dlp", &buffer) == 0);
}

// Função que faz o download e instalação manual da última versão do yt-dlp do GitHub
int instalar_yt_dlp_manual() {
    printf("Instalando yt-dlp manualmente (versão mais recente)...\n");
    // Executa um comando shell para baixar o arquivo 'yt-dlp' direto do repositório oficial para /usr/local/bin
    int resultado = system("sudo curl -L https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp -o /usr/local/bin/yt-dlp");
    if (resultado != 0) return 0; // Se falhar no download, retorna 0 (erro)
    // Altera as permissões para tornar o arquivo executável para todos os usuários
    return (system("sudo chmod a+rx /usr/local/bin/yt-dlp") == 0);
}

// Função para remover versão antiga do yt-dlp instalada via apt (gerenciador de pacotes do Debian/Ubuntu)
void remover_yt_dlp_apt() {
    printf("Removendo versão antiga do yt-dlp (via apt)...\n");
    // Comando para remover o pacote yt-dlp via apt, sem pedir confirmação (-y)
    system("sudo apt remove -y yt-dlp");
}

// Função que valida se a URL é provavelmente um link do YouTube
int url_valida(const char *url) {
    // strstr() verifica se a substring "youtube.com/watch" ou "youtu.be/" existe na URL
    // Se uma das duas estiver presente, a URL é considerada válida (retorna valor diferente de NULL que equivale a true)
    return strstr(url, "youtube.com/watch") || strstr(url, "youtu.be/");
}

int main(int argc, char *argv[]) {
    // Primeiro, verifica se o yt-dlp está instalado
    if (!verificar_yt_dlp()) {
        // Se não estiver instalado, pergunta para o usuário se quer instalar
        char resposta;
        printf("O programa 'yt-dlp' não está instalado.\nDeseja instalar agora? (s/n): ");
        scanf(" %c", &resposta);  // Lê um caractere, o espaço antes do %c ignora espaços em branco anteriores

        if (resposta == 's' || resposta == 'S') {
            // Se o usuário aceitar, tenta instalar manualmente
            if (!instalar_yt_dlp_manual()) {
                printf("Erro ao instalar o yt-dlp. Encerrando.\n");
                return 1; // Sai do programa com erro
            }
        } else {
            // Se o usuário não quiser instalar, encerra o programa
            printf("O programa não pode continuar sem o yt-dlp. Encerrando.\n");
            return 1;
        }
    }
    // Caso o yt-dlp já esteja instalado pelo sistema, verifica se a instalação manual não existe ainda
    else if (!yt_dlp_manual_instalado()) {
        // Se a instalação manual ainda não existe, remove a versão via apt e instala manualmente para garantir atualização
        remover_yt_dlp_apt();
        if (!instalar_yt_dlp_manual()) {
            printf("Erro ao atualizar o yt-dlp. Encerrando.\n");
            return 1;
        }
    }

    // Verifica se o usuário passou exatamente 1 argumento (o programa + URL = 2 argumentos)
    if (argc != 2) {
        printf("Uso: %s <URL do YouTube>\n", argv[0]);  // Mostra como usar o programa corretamente
        return 1;
    }

    // Pega a URL passada pelo usuário
    const char *url = argv[1];
    // Valida se a URL é de fato um link do YouTube (simplificado)
    if (!url_valida(url)) {
        printf("Erro: URL inválida. Informe um link válido do YouTube.\n");
        return 1;
    }

    // Monta o comando que será executado no terminal para baixar o vídeo com yt-dlp
    char comando[1024];
    // -P define o diretório de download, --progress mostra barra de progresso, a URL vem no final
    snprintf(comando, sizeof(comando),
             "yt-dlp -P %s --progress \"%s\"", DOWNLOAD_DIR, url);

    printf("Baixando vídeo...\n");
    // Executa o comando montado acima, o yt-dlp fará o download do vídeo
    int resultado = system(comando);

    // Verifica se o download foi realizado com sucesso (resultado 0 indica sucesso)
    if (resultado == 0) {
        printf("✅ Download concluído com sucesso!\n");
    } else {
        printf("❌ Falha ao baixar o vídeo.\n");
    }

    return 0;  // Finaliza o programa com sucesso
}

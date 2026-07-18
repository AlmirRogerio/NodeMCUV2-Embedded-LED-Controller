# NodeMCU WebServer

Web server embarcado no ESP8266 (NodeMCU v2) com gerenciamento WiFi via captive portal e controle de LED pela interface web.

## Funcionalidades

- **WiFi Manager** — Na primeira inicialização (ou quando não há credenciais salvas), o NodeMCU cria um Access Point (`NodeMCU-Setup`) com captive portal para configuração da rede WiFi.
- **Persistência em EEPROM** — As credenciais WiFi ficam salvas na EEPROM e sobrevivem a reinicializações.
- **Controle de LED** — Após conectado à rede, uma interface web permite ligar/desligar o LED onboard.
- **Reset de WiFi** — Botão na interface para apagar credenciais salvas e reiniciar no modo AP.
- **Captive Portal** — Redireciona automaticamente dispositivos conectados ao AP para a página de configuração.

## Como Funciona

1. O NodeMCU inicializa e verifica se há credenciais WiFi salvas na EEPROM.
2. **Se SIM** → Conecta na rede WiFi (modo STA) e serve a página de controle do LED.
3. **Se NÃO** → Cria um Access Point (modo AP) e serve o captive portal de configuração.

## Hardware

| Componente | Descrição |
|---|---|
| Board | NodeMCU v2 (ESP8266) |
| LED | LED onboard (`LED_BUILTIN`) |

## Estrutura do Projeto

```
├── include/
│   ├── config.h           # Constantes e configurações (pinos, endereços EEPROM, etc.)
│   ├── led_controller.h   # Interface do controlador de LED
│   ├── storage.h          # Interface de persistência (EEPROM)
│   ├── web_pages.h        # Interface das páginas HTML
│   ├── web_server.h       # Interface do web server
│   └── wifi_manager.h     # Interface do gerenciador WiFi
├── src/
│   ├── main.cpp           # Setup e loop principal
│   ├── led_controller.cpp # Controle do LED onboard
│   ├── storage.cpp        # Leitura/escrita na EEPROM
│   ├── web_pages.cpp      # HTML das páginas (config e controle)
│   ├── web_server.cpp     # Rotas e handlers HTTP
│   └── wifi_manager.cpp   # Conexão WiFi e modo AP
└── platformio.ini         # Configuração do PlatformIO
```

## Pré-requisitos

- [PlatformIO](https://platformio.org/) (extensão VSCode ou CLI)
- Cabo USB para conectar o NodeMCU ao computador

## Como Usar

### 1. Compilar e Enviar

```bash
# Via PlatformIO CLI
pio run --target upload

# Monitor serial
pio device monitor --baud 115200
```

Ou pelos atalhos do PlatformIO no VSCode:

| Ação | Atalho | Ícone na barra inferior |
|---|---|---|
| Build | `Ctrl+Alt+B` | ✓ |
| Upload | `Ctrl+Alt+U` | → |
| Serial Monitor | `Ctrl+Alt+S` |🔌 |

### 2. Configurar WiFi

1. Conecte-se à rede WiFi **NodeMCU-Setup** (sem senha).
2. O captive portal abrirá automaticamente. Se não abrir, acesse `http://192.168.4.1`.
3. Selecione sua rede WiFi, digite a senha e clique em **Conectar**.
4. O NodeMCU reiniciará e se conectará à rede escolhida.

### 3. Controlar o LED

1. Verifique no monitor serial o IP atribuído ao NodeMCU.
2. Acesse o IP no navegador (ex: `http://192.168.1.100`).
3. Use o botão **Alternar LED** para ligar/desligar.

### 4. Resetar WiFi

- Na página de controle, clique em **Resetar WiFi** para apagar as credenciais e voltar ao modo AP.

## Configuração

As constantes podem ser ajustadas em `include/config.h`:

| Constante | Padrão | Descrição |
|---|---|---|
| `AP_SSID` | `NodeMCU-Setup` | Nome da rede AP |
| `AP_PASS` | `""` (aberta) | Senha da rede AP |
| `WIFI_TIMEOUT_SEC` | `15` | Timeout de conexão WiFi (segundos) |
| `LED_PIN` | `LED_BUILTIN` | Pino do LED |
| `HTTP_PORT` | `80` | Porta do web server |

## Dependências

- **ESP8266WiFi** — Biblioteca WiFi nativa do ESP8266
- **ESP8266WebServer** — Web server HTTP
- **DNSServer** — DNS para captive portal
- **EEPROM** — Persistência de dados

Todas são bibliotecas nativas do framework Arduino para ESP8266 — não é necessário instalar nada além do PlatformIO.

## Licença

Este projeto é livre para uso pessoal e educacional.

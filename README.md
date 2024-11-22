Sistema de Monitoramento de energia e Controle com ESP32 via MQTT e interface web 

Simulação WOKWI - Observação: para a simulação as funcioanlidades de conexão por wifi e mqtt foram retiradas por não haver suporte na plataforma.
https://wokwi.com/projects/415290982399302657

Video de demostração:
https://youtu.be/cXemqMd5Luo

Este projeto implementa um sistema de monitoramento e controle baseado no ESP32, utilizando um botão, sensor PIR, dois relés e integração com um servidor MQTT para monitoramento em tempo real. A lógica do sistema permite automação eficiente, conectividade online e controle remoto por meio de uma interface MQTT.

🚀 Funcionalidades

	1.	Controle de Relés:
	•	Relé 1: Controlado pelo botão e sensor PIR, com desligamento automático após 10 minutos de inatividade.
	•	Relé 2: Sempre ligado.
	2.	Sensor PIR:
	•	Detecta movimento e, ao acioná-lo, liga o Relé 1.
	•	Zera a contagem de inatividade para manter o relé ativo.
	3.	Botão de Controle:
	•	Alterna manualmente entre ligar e desligar o Relé 1.
	4.	MQTT:
	•	Integração com servidor MQTT para monitoramento em tempo real.
	•	Envio de atualizações do estado do sistema (estado dos relés e tempo restante para desligamento do Relé 1).
	5.	Wi-Fi:
	•	Conexão à rede Wi-Fi para garantir comunicação com o servidor MQTT.
🛠️ Tecnologias Utilizadas

	•	Hardware:
	•	ESP32
	•	Relés
	•	Sensor PIR
	•	Botão
	•	Software:
	•	Arduino IDE
	•	Biblioteca WiFi (inclusa no Arduino para ESP32)
	•	Biblioteca PubSubClient para integração MQTT
	•	Protocolos:
	•	Wi-Fi (IEEE 802.11)
	•	MQTT (Message Queuing Telemetry Transport)
📜 Pré-requisitos

	1.	Hardware:
	•	ESP32.
	•	Sensor PIR.
	•	Dois módulos de relé.
	•	Um botão.
	•	Fonte de alimentação adequada.
	2.	Bibliotecas:
	•	WiFi (padrão para ESP32).
	•	PubSubClient para MQTT.
⚙️ Configuração do Ambiente

Passo 1: Instalar Bibliotecas

	•	Abra o Arduino IDE.
	•	Vá para Sketch > Incluir Biblioteca > Gerenciar Bibliotecas.
	•	Instale as bibliotecas:
	•	PubSubClient (desenvolvida por Nick O’Leary).

Passo 2: Configurar o Código

No código fornecido, configure as seguintes variáveis com as credenciais de sua rede e servidor MQTT:
const char* ssid = "SEU_SSID";              // Nome da rede Wi-Fi
const char* password = "SUA_SENHA_WIFI";    // Senha da rede Wi-Fi
const char* mqtt_server = "SEU_SERVIDOR_MQTT";  // Endereço do servidor MQTT
const char* mqtt_user = "SEU_USUARIO_MQTT";     // Usuário MQTT
const char* mqtt_password = "SUA_SENHA_MQTT";   // Senha MQTT

Passo 3: Conectar Componentes

Componente	Pino ESP32
Botão	GPIO40
Relé 1	GPIO38
Relé 2	GPIO39
Sensor PIR	GPIO37

🖥️ Fluxo do Sistema

	1.	Inicialização:
	•	O ESP32 conecta-se à rede Wi-Fi e ao servidor MQTT.
	•	O Relé 2 é ligado automaticamente.
	2.	Controle de Relé 1:
	•	Pelo botão: Alterna entre ligado/desligado.
	•	Pelo sensor PIR: Liga o relé e reinicia a contagem de inatividade.
	•	Desligamento automático: Após 10 minutos sem movimento detectado pelo PIR.
	3.	MQTT:
	•	Atualiza o estado do Relé 1:
	•	Ligado/desligado.
	•	Motivo (botão, PIR ou inatividade).
	•	Publica o tempo restante para o desligamento automático do Relé 1.

🔧 Personalizações

	1.	Intervalo de Inatividade:
	•	Alterar a variável checkInterval para modificar o tempo limite (em milissegundos):

const unsigned long checkInterval = 10 * 60 * 1000; // 10 minutos

	2.	Configurações MQTT:
	•	Personalizar os tópicos MQTT para monitorar e controlar o sistema:

🚦 Exemplo de Saída MQTT

Tópicos Publicados:

	1.	esp32/status:
	•	Publica mensagens gerais, como:

ESP32 conectado ao servidor MQTT!
Tempo restante: 599 segundos

	2.	esp32/relay1:
	•	Publica o estado e o motivo das alterações no Relé 1:

ligado
desligado
ligado pelo PIR
desligado por inatividade

🧪 Testando o Sistema

Simulação:

	1.	Botão:
	•	Pressione o botão conectado ao GPIO40 para alternar o estado do Relé 1.
	2.	Sensor PIR:
	•	Gire o sensor PIR para detectar movimento e observe o Relé 1 ligar.
	3.	MQTT:
	•	Use um cliente MQTT (ex.: MQTT Explorer ou Node-RED) para monitorar os tópicos.

📜 Licença

Este projeto está licenciado sob a licença MIT - veja o arquivo LICENSE para mais detalhes.

👨‍💻 Autor

Desenvolvido por:
Alan de Souza Maximiano – 557088.
Danilo Ramalho Silva – 555183
João Vitor Pires da Silva – 556213

Contato: alan.maximiano@gmail.com

🌟 Contribuições

Contribuições são bem-vindas! Siga as diretrizes descritas no arquivo CONTRIBUTING.md.


















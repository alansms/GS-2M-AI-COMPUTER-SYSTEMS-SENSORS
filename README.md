Sistema de Monitoramento e Controle com ESP32 via MQTT

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

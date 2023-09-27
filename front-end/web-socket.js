const chatBox = document.getElementById('chat');
const mensagemInput = document.getElementById('mensagemInput');
const enviarMensagemBotao = document.getElementById('enviarMensagemBotao');

// TODO Alterar para o IP da rede
const IP_LOCAL = '172.20.10.14';
const ws = new WebSocket(`ws://${IP_LOCAL}:81/`);
const webServerUrl = `http://${IP_LOCAL}:80/`;

// Lidar com mensagens recebidas do servidor WebSocket
ws.onmessage = function (event) {
    adicionarMensagem(event.data);
};

// Lidar com o envio de mensagens
enviarMensagemBotao.addEventListener('click', function () {
    const message = mensagemInput.value;
    enviarMensagem(message);
});

// Lidar com a tecla Enter
mensagemInput.addEventListener('keyup', function (event) {
    if (event.key === 'Enter') {
        const message = mensagemInput.value;
        enviarMensagem(message);
    }
});

/**
 * @param {string} message
 * @param message
 * @return {void}
 * Função para adicionar mensagens ao chatBox
 */
const adicionarMensagem = (message) => {
    const messageElement = document.createElement('div');
    messageElement.textContent = message;
    chatBox.appendChild(messageElement);
    chatBox.scrollTop = chatBox.scrollHeight;
}

/**
 * @param {string} message
 * @param message
 * @return {void}
 * Função para enviar mensagens ao servidor WebSocket
 */
const enviarMensagem = (message) => {
    const nomeUsuarioInput = document.getElementById('nomeInput').value || '';
    const mensagemCompleta = `${nomeUsuarioInput}: ${message}`;
    ws.send(mensagemCompleta);
    mensagemInput.value = '';
}

const buscarHistoricoMensagens = async () => {
    try {
        const response = await fetch(`${webServerUrl}mensagens-historico`);
        console.log('response')
        console.log(response)
        if (!response.ok) {
            throw new Error(`Erro na solicitação: ${response.status} ${response.statusText}`);
        }

        const data = await response.json();
        _atualizarListaDoHistoricoDeMensagens(data)
    } catch (error) {
        console.error('Erro ao obter o histórico de mensagens:', error);
    }
};
buscarHistoricoMensagens().then(r => console.info('Historico de mensagens carregado'));

const _atualizarListaDoHistoricoDeMensagens = (historicoMensagens) => {
    historicoMensagens.forEach(mensagem => adicionarMensagem(mensagem));
}
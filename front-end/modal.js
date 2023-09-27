const openModalButton = document.getElementById('openModal');
const modal = document.getElementById('modal');
const nomeDoUsuarioInput = document.getElementById('nomeInput')

const abreModal = () => {
    modal.style.display = 'block';
    nomeDoUsuarioInput.value = '';
}
abreModal();

const nomeDeveTerCincoDigito = () => {
    const nomeInputAtualizado = document.getElementById('nomeInput')
    nomeInputAtualizado.addEventListener('keyup', function () {
        _desabilitaBotaoEnviar()
    });
}

const _desabilitaBotaoEnviar = () => {
    document.getElementById('enviarNomeBotao').disabled = nomeDoUsuarioInput.value.length < 5;
}
nomeDeveTerCincoDigito();

const enviarNome = () => {
    const enviarNomeBotao = document.getElementById('enviarNomeBotao');

    // Lida com click
    enviarNomeBotao.addEventListener('click', function () {
        if (nomeDoUsuarioInput.value.trim() === '') return;
        modal.style.display = 'none';
    });

    // Lida com tecla Enter
    nomeDoUsuarioInput.addEventListener('keyup', function (event) {
        if (event.key === 'Enter') {
            if (nomeDoUsuarioInput.value.trim() === '') return;
            modal.style.display = 'none';
        }
    });
}
enviarNome();
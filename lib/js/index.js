function apiTesteCpp() {
    fetch('http://localhost:8080/api')
        .then((response) => {

            if (!response.ok) {
                throw new Error('Erro na requisição. Status: ' + response.status);
            }

            return response.json();
        })
        .then((res) => {
            console.log(res);
            // let tbodyDataExpense = document.querySelector('#tbodyDataExpense');

            // tbodyDataExpense.innerHTML = '';

            // let valueRowsTable = "";
            // res.data.forEach(element => {
            //     valueRowsTable += `<tr>
            //         <td>${element.id}</td>
            //         <td id="tdIdNome${element.id}" value="${element.nome}" >${element.nome}</td>
            //         <td id="tdIdEmail${element.id}" value="${element.mail}" >${element.mail}</td>
            //         <td class="icon-style"  onclick="editarAndDelete(${element.id},'edit')" ><i style="color:blue" class="fa-regular fa-pen-to-square"></i></td>
            //         <td class="icon-style" onclick="editarAndDelete(${element.id},'delete')" ><i style="color:red" class="fa-solid fa-trash"></i></td>
            //     </tr>`;
            // });

            // if (valueRowsTable) {
            //     tbodyDataExpense.innerHTML = valueRowsTable;
            // } else {
            //     tbodyDataExpense.innerHTML = 'Nenhum registro encontrado!';
            // }


        })
        .catch((error) => {
            console.error('Erro na requisição:', error);
        });

}

function renderPage() {
    fetch('http://localhost:8080/')
        .then((response) => {

            if (!response.ok) {
                throw new Error('Erro na requisição. Status: ' + response.status);
            }

            return response.json();
        })
        .then((res) => {
            if (res == "/teste") {
                console.log("Renderizar pagina")
            }
        })
        .catch((error) => {
            console.error('Erro na requisição:', error);
        });

}

function apiMethodNotGet(data, endPoint, method = 'POST', headers = {
    'Content-Type': 'application/json'
}) {
    const fetchOptions = {
        method,
        headers,
        body: JSON.stringify(data)
    };

    const apiUrl = `http://localhost:8080/${endPoint}`;

    fetch(apiUrl, fetchOptions)
        .then((response) => {
            if (!response.ok) {
                throw new Error('Erro na solicitação: ' + response.status);
            }
            return response.json();
        })
        .then((res) => {
            if (res.type === 'POST') {
                alert(res.mensage)
                document.querySelector('#name').value = '';
                document.querySelector('#email').value = '';
            } else if (res.type === 'PUT' || res.type === 'DELETE') {
                alert(res.mensage);
                const modal = document.querySelector('#modalDefautl');
                const modalDefautl = bootstrap.Modal.getInstance(modal);
                if (modalDefautl) {
                    modalDefautl.hide();
                }
                apiTesteCpp();
            }
        })
        .catch((error) => {
            console.error('Erro:', error.message);
        });
}

function editarAndDelete(id, type) {

    const btnPrimary = document.querySelector('#btnPrimaryModal');
    const btnSecondary = document.querySelector('#btnsecondaryModal');
    document.querySelector('#modalHeaderTitle').innerHTML = `${type === "edit" ? "Editar" : `Deletar`}`;

    if (type === "delete") {
        const nome = document.querySelector(`#tdIdNome${id}`);
        document.querySelector('#modalBody').innerHTML = `<input type="hidden" value="${id}" /><div style="display: flex;align-items: center;justify-content: center;" ><h5>Deseja deletar ${nome.getAttribute('value')} ?</h5></div>`;

        btnPrimary.innerHTML = 'Sim';
        btnPrimary.setAttribute('onclick', `deleteExpense(${id})`);
        btnSecondary.innerHTML = 'Não';

    } else {

        const nome = document.querySelector(`#tdIdNome${id}`);
        const email = document.querySelector(`#tdIdEmail${id}`);

        document.querySelector('#modalBody').innerHTML = `<input type="hidden" value="${id}" /><div class="mb-3"><label for="tdIdNomeUpdate${id}" class="form-label">Nome</label><input type="text" class="form-control" value="${nome.getAttribute('value')}" id="tdIdNomeUpdate${id}" ></div><div class="mb-3"><label for="tdIdEmailUpdate${id}" class="form-label">Email</label><input type="email" class="form-control" value="${email.getAttribute('value')}" id="tdIdEmailUpdate${id}" ></div>`;

        btnPrimary.innerHTML = 'Salvar';
        btnPrimary.setAttribute('onclick', `update(${id})`);
        btnSecondary.innerHTML = 'Fechar';

    }


    const modal = new bootstrap.Modal(document.getElementById('modalDefautl'));
    modal.show();
}

function update(id) {
    const nome = document.querySelector(`#tdIdNomeUpdate${id}`).value;
    const email = document.querySelector(`#tdIdEmailUpdate${id}`).value;

    const idInt = parseInt(id);

    const obj = {
        id: idInt,
        nome: nome,
        email: email
    }

    apiMethodNotGet(obj, 'api/put', 'PUT');
}

function deleteExpense(id) {

    const obj = {
        id: parseInt(id)
    }

    apiMethodNotGet(obj, 'api/delete', 'DELETE');
}

function showHide(displayNone, displayBlock) {
    if (displayBlock == 'divTableExpense') {
        apiTesteCpp();
    }
    document.querySelector(`#${displayNone} `).style.display = 'none';
    document.querySelector(`#${displayBlock} `).style.display = 'block';
}

function saveExpense(endPoint) {

    const data = {
        'nome': document.querySelector('#name').value,
        'email': document.querySelector('#email').value
    }

    apiMethodNotGet(data, endPoint)
}

function rederPage(page = "semesters") {
    fetch(`http://localhost:8080/${page}`)
        .then((response) => {            

            document.querySelector('#root').innerHTML = `<div style="height: 100vh;display: flex;align-items: center;justify-content: center;" ><i class="fas fa-spinner fa-spin"></i></div>`;     

            if (!response.ok) {
                throw new Error('Erro na requisição. Status: ' + response.status);
            }

            return response.text();
        })
        .then((res) => {
            document.querySelector('#root').innerHTML = res;
        })
        .catch((error) => {
            console.error('Erro na requisição:', error);
        });

}

document.addEventListener('DOMContentLoaded', function () {
    // document.querySelector('#divFormAddExpense').style.display = 'none';
    // apiTesteCpp();
    rederPage();
});
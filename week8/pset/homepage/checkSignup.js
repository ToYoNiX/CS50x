document.addEventListener('DOMContentLoaded', function() {
    document.querySelector('form').addEventListener('submit', function(event) {

        let warning = document.querySelector('#warning');
        let page = document.querySelector('form');

        if (!document.querySelector('#inputFirstName').value) {
            warning.innerHTML = "Missing First Name!";
        } else if (!document.querySelector('#inputLastName').value) {
            warning.innerHTML = "Missing Last Name!";
        } else if (!document.querySelector('#inputHandle').value) {
            warning.innerHTML = "Missing Handle!";
        } else if (!document.querySelector('#inputEmail').value) {
            warning.innerHTML = "Missing Email!";
        } else if (!document.querySelector('#inputPassword').value) {
            warning.innerHTML = "Missing Passward!";
        } else if (!document.querySelector('#checkTerms').checked) {
            warning.innerHTML = "You have to agree the terms!";
        } else {
            page.innerHTML = "Signed Up Successfully";
        }

        event.preventDefault();
    });
});

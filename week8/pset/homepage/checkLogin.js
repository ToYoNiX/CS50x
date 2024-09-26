document.addEventListener('DOMContentLoaded', function() {

    document.querySelector('form').addEventListener('submit', function(event) {
        let email = document.querySelector('#inputEmail').value;
        let pass = document.querySelector('#inputPassword').value;
        let page = document.querySelector('form');

        if (email == "toyonix@cs50x.edu" && pass == "I am Studying CS50x") {
            page.innerHTML = "Login Successful";
        } else {
            page.innerHTML = "Something is wrong!";
        }

        event.preventDefault();
    });

})

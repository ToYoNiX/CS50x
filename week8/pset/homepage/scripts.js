// The default content
$(function(){
    $("#includedContent").load("homePage.html");
});

// Run script once DOM is loaded
document.addEventListener('DOMContentLoaded', function(){
    // When home buttom is clicked, Change the content.
    let home = document.querySelector('.home');
    home.addEventListener('click', function(){
        $("#includedContent").load("homePage.html");
    });

    // When About Me buttom is clicked, Change the content.
    let aboutMe = document.querySelector('.aboutMe');
    aboutMe.addEventListener('click', function(){
        $("#includedContent").load("aboutMe.html");
    });

    // When About CS50 buttom is clicked, Change the content.
    let aboutCS50 = document.querySelector('.aboutCS50');
    aboutCS50.addEventListener('click', function(){
        $("#includedContent").load("aboutCS50.html");
    });
});
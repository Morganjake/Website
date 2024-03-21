document.body.addEventListener('mousemove', function(event) {
    if (event.target.id == "BoxBorder") {
        Captcha = document.getElementById("Box")

        var Xpos = Math.random() * window.innerWidth
        var YPos = Math.random() * (window.innerHeight - 140)

        Captcha.style.left = Xpos + "px";
        Captcha.style.top = YPos + "px";
    }
});

function VerifyCaptcha() {
    var Checkbox = document.getElementById("Checkbox");
    

    if (!Checkbox.checked) {
        var ErrorMessage = document.getElementById("ErrorMessage");
        ErrorMessage.textContent = "Please check the box to confirm that you are not a robot.";
        ErrorMessage.style.color = "red";
    }
    else {
        window.location.href = "2.html";
    }
}

// Disables right click
document.oncontextmenu = document.body.oncontextmenu = function() {return false;}
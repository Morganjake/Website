function validateCaptcha() {
    const captchaCheckbox = document.getElementById('captchaCheckbox');
    const captchaMessage = document.getElementById('captchaMessage');

    if (captchaCheckbox.checked) {
        captchaMessage.textContent = 'Captcha passed! You are not a robot.';
        captchaMessage.style.color = 'green';
    } else {
        captchaMessage.textContent = 'Please check the box to confirm that you are not a robot.';
        captchaMessage.style.color = 'red';
    }
}

document.body.addEventListener('mousemove', function(event) {
    if (event.target.classList.contains('BoxBorder')) {
        Captcha = document.getElementById("Box")

        var Xpos = (Math.random() * window.innerWidth)
        var YPos = (Math.random() * window.innerHeight)

        Captcha.style.left = Xpos + "px";
        Captcha.style.top = YPos + "px";
    }
});
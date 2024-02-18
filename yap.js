document.addEventListener("DOMContentLoaded", function() {
    
    createCircle(window.innerWidth / 2, window.innerHeight / 2, 180, 180, 5, 5);

    function createCircle(X, Y, Width, Height, SpeedX, SpeedY) {
        var Yap = document.createElement('img');
        Yap.className = 'gif';
        Yap.src = "Images/Yap.gif"
        Yap.width = Width
        Yap.height = Height
        document.body.appendChild(Yap);
        moveCircle(Yap, X, Y, SpeedX, SpeedY);
    }


    function moveCircle(circle, X, Y, SpeedX, SpeedY) {
        circle.style.left = X + 'px';
        circle.style.top = Y + 'px';

        function update() {
            var XPos = parseInt(circle.style.left) || 0;
            var YPos = parseInt(circle.style.top) || 0;

            var NewXPos = XPos + SpeedX;
            var NewYPos = YPos + SpeedY;

            // Check for collisions with container walls
            if (NewXPos < 0 || NewXPos > (window.innerWidth - circle.offsetWidth)) {
                SpeedX *= -1; // Reverse direction
            }
            if (NewYPos < 0 || NewYPos > (window.innerHeight - circle.offsetHeight)) {
                SpeedY *= -1; // Reverse direction
            }

            circle.style.left = NewXPos + 'px';
            circle.style.top = NewYPos + 'px';

            requestAnimationFrame(update);
        }

        update();
    }


    document.body.addEventListener('click', function(event) {
        if (event.target.classList.contains('gif')) {

            var Pos = event.target.getBoundingClientRect()
            
            // Sets the speed of the balls
            var SpeedX = (Math.random() * 5 + 5) * (Math.random() < 0.5 ? 1 : -1) * Math.pow(180 / Pos.height, 0.4);
            var SpeedY = (Math.random() * 5 + 5) * (Math.random() < 0.5 ? 1 : -1) * Math.pow(180 / Pos.height, 0.4);

            // Creates two new balls that move in opposite directions then removes the clicked ball
            createCircle(Pos.x, Pos.y, Pos.width * 0.96, Pos.height * 0.96, SpeedX, SpeedY);
            createCircle(Pos.x, Pos.y, Pos.width * 0.96, Pos.height * 0.96, SpeedX * -1, SpeedY * -1);
            event.target.remove();
        }
    });
});
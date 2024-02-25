document.addEventListener("DOMContentLoaded", function() {
    
    CreateYap(window.innerWidth / 2, window.innerHeight / 2, 180, 180, 5, 5);

    function CreateYap(X, Y, Width, Height, SpeedX, SpeedY) {
        var Yap = document.createElement("img");
        Yap.className = "gif";
        Yap.src = "Images/Yap.gif"
        Yap.width = Width
        Yap.height = Height
        document.body.appendChild(Yap);
        MoveYap(Yap, X, Y, SpeedX, SpeedY);
    }


    function MoveYap(Yap, X, Y, SpeedX, SpeedY) {
        Yap.style.left = X + "px";
        Yap.style.top = Y + "px";

        function UpdatePosition() {
            var XPos = parseInt(Yap.style.left) || 0;
            var YPos = parseInt(Yap.style.top) || 0;

            var NewXPos = XPos + SpeedX;
            var NewYPos = YPos + SpeedY;

            // Check for collisions with container walls
            if (NewXPos < 0 || NewXPos > (window.innerWidth - Yap.offsetWidth)) {
                SpeedX *= -1; // Reverse direction
            }
            if (NewYPos < 0 || NewYPos > (window.innerHeight - Yap.offsetHeight)) {
                SpeedY *= -1; // Reverse direction
            }

            Yap.style.left = NewXPos + "px";
            Yap.style.top = NewYPos + "px";

            requestAnimationFrame(UpdatePosition); // Calls the function every frame
        }

        UpdatePosition();
    }


    document.body.addEventListener("click", function(event) {
        if (event.target.classList.contains("gif")) {

            var Pos = event.target.getBoundingClientRect()
            
            // Sets the speed of the balls
            var SpeedX = (Math.random() * 5 + 5) * (Math.random() < 0.5 ? 1 : -1) * Math.pow(180 / Pos.height, 0.4);
            var SpeedY = (Math.random() * 5 + 5) * (Math.random() < 0.5 ? 1 : -1) * Math.pow(180 / Pos.height, 0.4);

            // Creates two new balls that move in opposite directions then removes the clicked ball
            CreateYap(Pos.x, Pos.y, Pos.width * 0.96, Pos.height * 0.96, SpeedX, SpeedY);
            CreateYap(Pos.x, Pos.y, Pos.width * 0.96, Pos.height * 0.96, SpeedX * -1, SpeedY * -1);
            event.target.remove();
        }
    });
});
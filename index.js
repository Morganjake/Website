// Holds the previous mouse position
var PreviousMousePosX, PreviousMousePosY;
var MouseBlurColour = 0;

// Get the blur containers
var MouseBlurContainer = document.getElementById('MouseBlurContainer');
var ClickBlurContainer = document.getElementById('ClickBlurContainer');


function GetPixelsBetweenPoints(x0, y0, x1, y1) {
    // Uses Bresenham's line drawing algorithm to get every pixel
    var pixels = [];
    var dx = Math.abs(x1 - x0);
    var dy = Math.abs(y1 - y0);
    var sx = (x0 < x1) ? 1 : -1;
    var sy = (y0 < y1) ? 1 : -1;
    var err = dx - dy;
    var step = 15;
    var count = 0;

    while (true) {
        // Only adds every 15th pixels to reduce lag
        if (count % step === 0) {
            pixels.push({ x: x0, y: y0 });
        }
        count++;

        if ((x0 === x1) && (y0 === y1)) break;

        var e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }

    return pixels;
}


function CreateBlur(X, Y) {
    // Creates a new blur
    var MouseBlur = document.createElement('div');
    MouseBlur.className = 'MouseBlur';
    MouseBlurContainer.appendChild(MouseBlur);
    // Update the position of the blur element based on the mouse coordinates
    MouseBlur.style.left = X - MouseBlur.offsetWidth / 2 + 'px';
    MouseBlur.style.top = Y - MouseBlur.offsetHeight / 2 + 'px';

    // Sets the colour of the mouse blur
    MouseBlurColour = (MouseBlurColour + 1) % 360;
    MouseBlur.style.backgroundColor = `hsla(${MouseBlurColour}, 100%, 50%, 0.1)`;

    // Fading effect
    MouseBlur.style.opacity = 0;

    // Removes the blurs
    setTimeout(() => {
        MouseBlurContainer.removeChild(MouseBlur);
    }, 500);
}


// Event listener to track mouse movement
document.addEventListener('mousemove', function (screen) {

    if (PreviousMousePosX !== undefined && PreviousMousePosY !== undefined) {
        var pixels = GetPixelsBetweenPoints(PreviousMousePosX, PreviousMousePosY, screen.pageX, screen.pageY);
        pixels.forEach(function (pixel) {  // Loops over each pixel between the last and current mouse position
            CreateBlur(pixel.x, pixel.y);
        });
    }
    PreviousMousePosX = screen.pageX;
    PreviousMousePosY = screen.pageY;
});


// Event listener for mouse clicks
document.addEventListener('click', function (screen) {
    // Creates a new blur
    var ClickBlur = document.createElement('div');
    ClickBlur.className = 'ClickBlur';
    ClickBlurContainer.appendChild(ClickBlur);
    // Update the position of the blur element based on the mouse coordinates
    ClickBlur.style.left = screen.pageX - ClickBlur.offsetWidth / 2 + 'px';
    ClickBlur.style.top = screen.pageY - ClickBlur.offsetHeight / 2 + 'px';

    // Sets the colour of the mouse blur
    MouseBlurColour = (MouseBlurColour + 5) % 360;
    ClickBlur.style.borderColor = `hsla(${MouseBlurColour}, 100%, 50%, 0.3)`;                

    ClickBlur.classList.toggle('grown');

    // Removes the blurs
    setTimeout(() => {
        ClickBlurContainer.removeChild(ClickBlur);
    }, 2000);
});

// Gets the Mind palace stuff
var MindPalaceContainer = document.getElementById("MindPalace");
var MindPalaceImage = document.getElementById("MindPalaceImage");
var MindPalaceLensFlareLeft = document.querySelector(".MindPalaceLensFlareLeft");
var MindPalaceLensFlareRight = document.querySelector(".MindPalaceLensFlareRight");
var MindPalaceText = document.querySelector(".MindPalaceText");
var LensFlareBrightness = 0.9;
var LensFlareIsGettingBrighter;

MindPalaceImage.addEventListener('mouseover', function () {

    MindPalaceContainer.style.scale = 1.2;
    MindPalaceLensFlareLeft.style.opacity = 1;
    MindPalaceLensFlareRight.style.opacity = 1;
    MindPalaceText.style.transform = `translateY(70px)`;  // Distance the text 
});


MindPalaceImage.addEventListener('mouseout', function () {
    MindPalaceContainer.style.scale = 1;
    MindPalaceLensFlareLeft.style.opacity = 0;
    MindPalaceLensFlareRight.style.opacity = 0;
    MindPalaceText.style.transform = `translateY(0px)`
    MindPalaceLensFlareLeft.style.filter = `brightness(0.9)`;
    MindPalaceLensFlareRight.style.filter = `brightness(0.9)`;
    clearInterval(LensFlareIsGettingBrighter);
});


function MakeLensFlaresBrighter() {
    LensFlareBrightness = LensFlareBrightness + 0.015;
    MindPalaceLensFlareLeft.style.filter = `brightness(${LensFlareBrightness})`;
    MindPalaceLensFlareRight.style.filter = `brightness(${LensFlareBrightness})`;
}


function StartMakingLensFlaresBrighter() {
    LensFlareBrightness = 0.9;
    LensFlareIsGettingBrighter = setInterval(MakeLensFlaresBrighter, 0);
}


MindPalaceImage.addEventListener('click', function () {
    window.location.href = "brainrot.html";
});


var YapSessionContainer = document.getElementById("YapSession");
var YapSessionText = document.querySelector(".YapSessionText");


YapSessionImage.addEventListener('mouseover', function () {

    YapSessionContainer.style.scale = 1.2;
    YapSessionText.style.transform = `translateY(7000px)`;
});


YapSessionImage.addEventListener('mouseout', function () {
    YapSessionContainer.style.scale = 1;
    YapSessionText.style.transform = `translateY(0px)`;
});


YapSessionImage.addEventListener('click', function () {
    window.location.href = "yap.html";
});
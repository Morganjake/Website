var Board = document.getElementById("Board");
var ItemList = document.getElementById("List");
var InnerItemList = document.getElementById("ListInner");
var Dragging = false;
var DraggedItem;
var DraggedItemOffsetX = 0;
var DraggedItemOffsetY = 0;
var DiscoveredItems = ["Water", "Fire", "Earth", "Air"]

function IsOverlapping(Item1, Item2) {
    var Rect1 = Item1.getBoundingClientRect()
    var Rect2 = Item2.getBoundingClientRect()
    return !(
        Rect1.right < Rect2.left || 
        Rect1.left > Rect2.right || 
        Rect1.bottom < Rect2.top || 
        Rect1.top > Rect2.bottom
    );
}


function CanCombine(Item1, Item2, Material1, Material2) {

    if (Item1.innerHTML == Material1 && Item2.innerHTML == Material2) {
        return true
    }

    else if (Item1.innerHTML == Material2 && Item2.innerHTML == Material1) {
        return true
    }

    return false
}


function Combine(Item1, Item2) {

    const Combinations = [
        ["Water", "Fire", "Obsidian"],
        ["Water", "Earth", "Mud"],
        ["Water", "Air", "Cloud"],
        ["Fire", "Air", "Smoke"],
        ["Fire", "Earth", "Volcano"],
        ["Earth", "Air", "Dust"],
        ["Cloud", "Water", "Rain"],
        ["Fire", "Dust", "Ash"],
        ["Mud", "Rain", "Bog"],
        ["Rain", "Ash", "Smoke"],
        ["Obsidian", "Fire", "Lava"],
        ["Obsidian", "Volcano", "Lava"],
    ];

    for (let i = 0; i < Combinations.length; i++) {
        if (CanCombine(Item1, Item2, Combinations[i][0], Combinations[i][1])) {
            Item1.remove()
            Item2.innerHTML = Combinations[i][2]
            if (!DiscoveredItems.includes(Combinations[i][2] )) {
                AddItemToList(Combinations[i][2])
            }
            return true
        }
    }
    return false
}


function AddItemToList(ItemName) {
    var Item = document.createElement("div")
    Item.classList.add('Item');
    Item.innerHTML = ItemName
    InnerItemList.appendChild(Item);
    DiscoveredItems.push(ItemName)
}


document.body.addEventListener("click", function(event) {
    if (event.target.classList.contains("Item") && !event.target.classList.contains("OnBoard")) {
        var Item = event.target.cloneNode(true);
        Item.classList.add('OnBoard');
        var Rect = Board.getBoundingClientRect()
        var XPos = Rect.width / 4 + (Rect.width - Rect.width / 2) * Math.random();
        var YPos = Rect.height / 4 + (Rect.height - Rect.height / 2) * Math.random();
        Item.style.left = XPos + "px";
        Item.style.top = YPos + "px";
        Board.appendChild(Item);
    }
});


document.body.addEventListener("mousedown", function(event) {
    if (event.target.classList.contains("Item")) {
        Dragging = true;
        DraggedItem = event.target;
        DraggedItemOffsetX = event.clientX - event.target.getBoundingClientRect().left;
        DraggedItemOffsetY = event.clientY - event.target.getBoundingClientRect().top;
    }
});


document.body.addEventListener("mousemove", function(event) {
    if (Dragging) {
        DraggedItem.style.left = `${event.clientX - DraggedItemOffsetX}px`;
        DraggedItem.style.top = `${event.clientY - DraggedItemOffsetY}px`;
    }
});


document.body.addEventListener("mouseup", function(event) {
    Dragging = false;
    DraggedItem = null;

    if (event.target.classList.contains("OnBoard")) {
        if (IsOverlapping(ItemList, event.target)) {
            event.target.remove();
            return;
        }

        var AllItems = Board.children;
        for (let i = 0; i < AllItems.length; i++) {
            if (AllItems[i] != event.target && IsOverlapping(AllItems[i], event.target)) {
                if (Combine(AllItems[i], event.target)) {
                    break;
                }
            }
        }
    }
});



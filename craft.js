var Board = document.getElementById("Board");
var ItemList = document.getElementById("List");
var InnerItemList = document.getElementById("ListInner");
var Dragging = false;
var DraggedItem;
var DraggedItemOffsetX = 0;
var DraggedItemOffsetY = 0;
var DiscoveredItems = ["Water", "Fire", "Earth", "Air"]

// ChatGPT generated this code but it checks if elements are overlapping
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


// Compares both materials against the Item labels
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

    // List of all possible combinations (index 0 and 1 are the ingredients, index 2 is the product)
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
        ["Rain", "Earth", "Grass"],
        ["Water", "Mud", "Swamp"],
        ["Rain", "Mud", "Bog"],
        ["Fire", "Grass", "Ash"],
        ["Grass", "Earth", "Tree"],
        ["Mud", "Fire", "Brick"],
        ["Water", "Dust", "Sand"],
        ["Water", "Sand", "Beach"],
        ["Sand", "Fire", "Glass"],
        ["Glass", "Brick", "House"],
        ["Cloud", "Rain", "Storm"],
        ["Storm", "Fire", "Lightning"],
    ];

    // Loops through the combinations to see if it exists
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


// Adds the item to the item list
function AddItemToList(ItemName) {
    var Item = document.createElement("div")
    Item.classList.add("Item");
    Item.innerHTML = ItemName
    InnerItemList.appendChild(Item);
    DiscoveredItems.push(ItemName)
}


// Creates the selected item on the board
document.body.addEventListener("click", function(event) {
    if (event.target.classList.contains("Item") && !event.target.classList.contains("OnBoard")) {
        var Item = event.target.cloneNode(true);
        Item.classList.add("OnBoard");
        var Rect = Board.getBoundingClientRect()
        var XPos = Rect.width / 4 + (Rect.width - Rect.width / 2) * Math.random();
        var YPos = Rect.height / 4 + (Rect.height - Rect.height / 2) * Math.random();
        Item.style.left = XPos + "px";
        Item.style.top = YPos + "px";
        Board.appendChild(Item);
    }
});


// Checks if you have clicked on an item
document.body.addEventListener("mousedown", function(event) {
    if (event.target.classList.contains("Item")) {
        Dragging = true;
        DraggedItem = event.target;
        DraggedItemOffsetX = event.clientX - event.target.getBoundingClientRect().left;
        DraggedItemOffsetY = event.clientY - event.target.getBoundingClientRect().top;
    }
});


// Keeps the selected item at the mouse position
document.body.addEventListener("mousemove", function(event) {
    if (Dragging) {
        DraggedItem.style.left = `${event.clientX - DraggedItemOffsetX}px`;
        DraggedItem.style.top = `${event.clientY - DraggedItemOffsetY}px`;
    }
});


document.body.addEventListener("mouseup", function(event) {
    Dragging = false;
    DraggedItem = null;

    // Deletes it if it is over the item list
    if (event.target.classList.contains("OnBoard")) {
        if (IsOverlapping(ItemList, event.target)) {
            event.target.remove();
            return;
        }

        // Tries to combine the selected item with all the overlapping items
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



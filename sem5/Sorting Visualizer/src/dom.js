let algSelect;
let nSelect;
let startButton;
let randomButton;
let sortedButton;
let shuffleButton;
let reversedButton;
let resetButton;
let helpButton;
let uploadButton;

function initDOM() {
    algSelect = document.getElementById('alg-select');
    nSelect = document.getElementById('n-select');
    startButton = document.getElementById('start-button');
    randomButton = document.getElementById('random-button');
    sortedButton = document.getElementById('sorted-button');
    shuffleButton = document.getElementById('shuffle-button');
    reversedButton = document.getElementById('reversed-button');
    resetButton = document.getElementById('reset-button');
    helpButton = document.getElementById('help-button');
    uploadButton = document.getElementById('upload-button');

    algSelect.onchange = () => {
        reset();
        updateCurrentAlgorithm(algSelect);
        generateRandomArray();
    };

    nSelect.onchange = () => {
        reset();
        updateElementCount(nSelect);
        generateRandomArray();
    };

    for (let a in algorithmNames) {
        if (algorithmNames.hasOwnProperty(a)) {
            let opt = document.createElement('option');
            opt.appendChild(document.createTextNode(a));
            opt.value = algorithmNames[a];
            opt.classList.add('nav-bar-select-item');
            algSelect.appendChild(opt);

        }
    }

    for (let i = 8; i <= 512; i *= 2) {
        let opt = document.createElement('option');
        opt.appendChild(document.createTextNode(i.toString()));
        opt.value = i.toString();
        opt.classList.add('nav-bar-select-item');
        nSelect.appendChild(opt);
    }

    updateCurrentAlgorithm(algSelect);
    updateElementCount(nSelect);

    startButton.onclick = () =>{
        reset();
        lastOperationTime = callSortFunction(currAlg);
        drawingStatus = true;
    };

    randomButton.onclick = () => {
        generateRandomArray();
        reset();
    };

    sortedButton.onclick = () => {
        generateOrderedArray();
        reset();
    };

    shuffleButton.onclick = () => {
        arr = shuffleArray(arr);
        reset();
    };

    reversedButton.onclick = () => {
        generateOrderedArray();
        arr = arr.reverse();
        reset();
    };

    resetButton.onclick = reset;

    uploadButton.onclick=()=>{
        if(loopStatus!=='loop'){
        readFile();
        elementCount=arr.length;
        reset();
        }
    }
    function readFile(){
            console.log(`inside readFile`);
            const inputFile = document.querySelector('#help-button');
            const fileReader = new FileReader();
            fileReader.onload = e => {
            arr = e.target.result.split('\n');
            arr=arr.map((element)=>{
            return parseInt(element.replace('\r',''),10);
        })
        console.log(`Array: ${arr}`);
        calculateArray(arrayExt(arr));
      };
      fileReader.readAsText(inputFile.files[0], 'UTF-8');
    }

function generateOrderedArray() {
    if (loopStatus !== 'loop') {
        arr = orderedArray(elementCount);
        calculateArray(arrayExt(arr));
    }
}

function generateRandomArray() {
    if (loopStatus !== 'loop') {
        arr = randomArray(elementCount, 1, 50);
        calculateArray(arrayExt(arr));
    }
}

function updateElementCount(selector) {
    elementCount = getElementCount(selector);
}

function getElementCount(selector) {
    return parseInt(selector.value);
}

function updateCurrentAlgorithm(selector) {
    currAlg = getAlgorithmName(selector)
}

function getAlgorithmName(selector) {
    return selector.value;
}
}

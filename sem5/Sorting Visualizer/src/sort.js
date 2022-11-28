let stepCount=0;

async function callSortFunction(fName) {
    allArr = [];
    drawingStatus = true;
    loopStatus = "loop";
    let before;
    let after;

    before = millis();

    switch (fName) {
        case 'bubbleSort':
            await bubbleSort(arr.slice());
            break;
        case 'quickSort':
            await quickSort(arr.slice(), 0, arr.length - 1);
            break;
        case 'mergeSort':
            await mergeSort(arr.slice(), 0, arr.length - 1);
            break;
        case 'insertionSort':
            await insertionSort(arr.slice());
            break;
        case 'heapSort':
            await heapSort(arr.slice());
            break;
        case 'radixSort':
            if (arr.some(e => e !== Math.floor(e))) {
                alert('Radix sort can be applied to integer values');
                return 0;
            } else {
                await radixSort(arr.slice());
            }
            break;
        case 'countSort':
            console.log(`countsort option selected`);
            if (arr.some(e => e !== Math.floor(e))) {
                alert('Count sort can be applied to integer values');
                return 0;
            }else if(arr.some(e => e<0)){
                alert('Negative numbers not allowed for Count Sort')
            }else
            await Countsort(arr.slice());
            break;
    }

    after = millis();
    document.getElementById('sorted').style.display='block';
    return after - before;
}

async function bubbleSort(a) {
    let stepsBox=document.getElementById('stepsBox');
    let cnter=document.getElementById('counter');
    for (let i = 0; i < a.length - 1; i++) {
        for (let j = 0; j < a.length - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                allArr.push(a.slice());//render before swap
                await sleep();
                cnter.classList.remove('green');
                stepCount++;
                stepsBox.innerHTML+=`${stepCount}. Element ${a[j]} at index ${j} is greater than element ${a[j+1]} at index ${j+1}\n`;
                console.log(`${stepCount}. Element ${a[j]} at index ${j} is greater than element ${a[j+1]} at index ${j+1}`);
                let tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                allArr.push(a.slice());//render after swap
                stepCount++;
                stepsBox.innerHTML+=`${stepCount}. Swapping elements ${a[j]} and ${a[j+1]}\n`;
                await sleep();
                cnter.classList.add('green');
                cnter.innerText=`${stepCount/2}`;
                console.log(`${stepCount}. Swapping elements ${a[j]} and ${a[j+1]}`);
            }
        }
    }
    allArr.push(a.slice());
    stepCount=0;
}

function sleep() {
    return new Promise(resolve => setTimeout(resolve, 150));
}

async function quickSort(a, low, high) {
    if (low < high) {
        let pIndex = await quickSortPartition(a, low, high);
        quickSort(a, low, pIndex - 1);
        quickSort(a, pIndex + 1, high);
    }
}

async function quickSortPartition(a, low, high) {
    let pivot = a[high];

    let i = low - 1;
    for (let j = low; j < high; j++) {
        if (a[j] < pivot) {
            console.log(`inside pivot`);
            //await sleep();
            allArr.push(a.slice());
            i++;

            let tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }

    allArr.push(a.slice());
    i++;
    console.log(`calling sleep outside loop in pivot`);
    await sleep();
    let tmp = a[high];
    a[high] = a[i];
    a[i] = tmp;
    allArr.push(a.slice());

    return i;
}

async function mergeSort(a, low, high) {
    if (low < high) {
        let mid = parseInt(((low + high) / 2).toString());
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        await merge(a, low, mid, high);
    }
}

async function merge(a, low, mid, high) {
    let n1 = mid - low + 1;
    let n2 = high - mid;

    let l = new Array(n1);
    let r = new Array(n2);

    for (let i = 0; i < n1; i++) {
        l[i] = a[low + i];
    }

    for (let i = 0; i < n2; i++) {
        r[i] = a[mid + i + 1];
    }

    let i = 0;
    let j = 0;
    let k = low;

    while (i < n1 && j < n2) {
        if (l[i] <= r[j]) {
            a[k] = l[i];
            i++;
        } else {
            a[k] = r[j];
            j++;
        }

        k++;
        allArr.push(a.slice());
        //await sleep();
    }

    while (i < n1) {
        a[k] = l[i];
        i++;
        k++;
        //await sleep();
        allArr.push(a.slice());
    }

    while (j < n2) {
        a[k] = r[j];
        j++;
        k++;
        //await sleep();
        allArr.push(a.slice());
    }
        await sleep();
        allArr.push(a.slice());
}

async function insertionSort(a) {
    for (let i = 0; i < a.length; i++) {
        let current = a[i];
        let j = i - 1;

        while (j >= 0 && a[j] > current) {
            a[j + 1] = a[j];
            j--;

            allArr.push(a.slice());
        }

        a[j + 1] = current;
        allArr.push(a.slice());
    }
}

async function heapSort(a) {
    for (let i = Math.floor(a.length / 2) - 1; i >= 0; i--) {
        heapify(a, a.length, i);
    }

    for (let i = a.length - 1; i >= 0; i--) {
        let tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;

        allArr.push(a.slice());

        await heapify(a, i, 0);
    }
}

async function heapify(a, n, i) {
    let largest = i;
    let l = 2 * i + 1;
    let r = 2 * i + 2;

    if (l < n && a[l] > a[largest]) {
        largest = l;
    }

    if (r < n && a[r] > a[largest]) {
        largest = r;
    }

    if (largest !== i) {
        let tmp = a[i];
        a[i] = a[largest];
        a[largest] = tmp;

        allArr.push(a.slice());

        heapify(a, n, largest);
    }
}

async function radixSort(a) {
    let max = Math.max(...a); // Get maximum element
    for (let exp = 1; Math.floor(max / exp) > 0; exp *= 10) {
        await countSort(a, exp);
    }
}

async function countSort(a, exp) {
    let output = new Array(a.length).fill(0);
    let count = new Array(10).fill(0);

    for (let i = 0; i < a.length; i++) {
        count[ Math.floor(a[i] / exp) % 10 ]++;
    }

    for (let i = 1; i < 10; i++) {
        count[i] += count[i-1];
    }

    for (let i = a.length - 1; i >= 0; i--) {
        output[count[Math.floor(a[i]/exp)%10]-1] = a[i];
        count[Math.floor(a[i]/exp)%10]--;
    }

    for (let i = 0; i < a.length; i++) {
        a[i] = output[i];
        allArr.push(a.slice());
        await sleep();
    }
}

async function Countsort(a) {
    console.log(`Inside countsort function`);
    var n = a.length;
    let max = Math.max(...a);
    console.log(`Unsorted Array: ${a}`);
    let output = new Array(n).fill(0);
    let count = new Array(max+1).fill(0);
    for (var i = 0; i < n; ++i)
        ++count[a[i]];

        for (var i = 1; i <max+1; ++i)
        count[i] += count[i - 1];
 
        for (var i = n - 1; i >= 0; i--) {
        output[count[a[i]] - 1] = a[i];
        --count[a[i]];
    }
 
    for (var i = 0; i < n; ++i){
        a[i] = output[i];
        allArr.push(a.slice());
        await sleep();
    }
    console.log(`array sorted: ${a}`);
}
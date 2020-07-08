## Внешняя и внутренняя сортировка
### Задание
Сгенерировать массив элементов, состоящих из трёх числовых полей и двух строковых.
Записей причем может быть больше 1000. На этом массиве реализовать внешнюю сортировку естественным слиянием с порогом,
а внутреннюю сортировку пирамидальной сортировкой.

### Алгоритм
Суть метода естественного слияния с порогом в работе заключается в том, что для начала мы создаем блок записей случайной величины.
Случайная величина выбирается для блока, в границах от 1 до 1000, для удобства сортировки.
Данный блок мы пишем в отдельный файл (временный файл). 
После мы сортируем данный блок внутренней сортировкой и пишем его в другой файл, в первый файл отсортированных блоков.
И в конце данного блока пишем порог. Порог в нашем случае – это нереальная запись, или запись с невозможными данными.
Следующий блок мы пишем в файл 2, аналогичный первому. И так мы повторяем эти действия, попеременно записывая блока то в первый,
то во второй файл, пока не сгенерируются N заданных записей.<br/><br/>
Далее уже идет второй этап сортировки, в которой мы сливаем два файла с отсортированными блоками в один отсортированный файл.<br/><br/>
Это происходит следующим путём. Мы для начала вызываем функцию слияния файлов. Данная функция сливает по два блока из разных файлов. Процесс описан ниже.<br/><br/>
Мы извлекаем в начале по строке из первого и второго файла.
Далее мы проверяем является ли первая строка порогом, если да, то переписываем весь блок из второго файла,
то есть считываем строки и пишем их в файл, пока не дойдем до порога. Пишем порог. Если строка из первого файла не равна порогу,
то если вторая строка равна порогу, то выполняем аналогичные действия, только записывая блок из первого файла. Есть третий вариант,
когда все-таки строки не равны порогам, тогда мы сравниваем строки и пишем их в порядке возрастания. Извлекает строки и переходим в начало выполнения функции,
если в обоих файлах не дошли до конца. Если мы дошли до конца, то мы вызываем функцию разделения этого файла со слитыми попарно блоками на два файла. 
И опять вызываем функцию слияния и так, пока не сольем все блоки, то есть не получим отсортированный массив записей.

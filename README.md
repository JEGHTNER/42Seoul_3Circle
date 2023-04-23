# 42Seoul_3Circle
42Seoul 3Circle Projects

<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
	<h1>Philo</h1>
  <p>Philo is a program that simulates the dining philosophers problem. The problem involves a group of philosophers who are seated around a table. There are forks placed between each pair of adjacent philosophers. The philosophers must alternate between thinking and eating. To eat, a philosopher must pick up the two forks next to them. The goal of the problem is to find a solution that allows the philosophers to eat without causing a deadlock or a starvation.</p>

<h2>Usage</h2>

<p>To use the philo program, run it with the following arguments:</p>

<pre><code>./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
</code></pre>

<ul>
	<li><code>number_of_philosophers</code> - the number of philosophers sitting at the table</li>
	<li><code>time_to_die</code> - the maximum time a philosopher can go without eating before they die</li>
	<li><code>time_to_eat</code> - the time it takes for a philosopher to eat</li>
	<li><code>time_to_sleep</code> - the time a philosopher spends sleeping between meals</li>
	<li><code>number_of_times_each_philosopher_must_eat</code> (optional) - the number of times each philosopher must eat before the program exits</li>
</ul>

<p>The program will output a log of each philosopher's actions, including when they start eating, sleeping, and thinking, as well as when they die. The program will exit when all philosophers have eaten the required number of times or when a philosopher dies.</p>

<h2>Examples</h2>

<p>Here is an example of how to use the philo program:</p>

<pre><code>./philo 5 800 200 200
</code></pre>

<p>This code will simulate a table with 5 philosophers, a maximum time to live of 800ms, a time to eat of 200ms, and a time to sleep of 200ms.</p>
</body>
</html>





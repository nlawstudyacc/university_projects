defmodule Philosopher do
  @eatingRange 10
  @dreamingRange 100

  #start(hunger, right, left, name, ctrl)

  def start(hunger, right, left, name, ctrl, waiter) do
    spawn_link(fn -> dreamingPhilosopher(hunger, right, left, name, ctrl, waiter) end)
  end

  def dreamingPhilosopher(0, _right, _left, name, ctrl, _waiter) do
    IO.puts("--> Philosopher #{name} is well fed")
    send(ctrl, :done)
  end

  def dreamingPhilosopher(hunger, right, left, name, ctrl, waiter) do
    IO.puts("Philosopher #{name} is dreaming but quite hungry. Hunger: #{hunger}")

    sleep(@dreamingRange)

    IO.puts("Philosopher #{name} has woken up")

    waitingPhilosopher(hunger, right, left, name, ctrl, waiter)
  end

  #changed state for asynchronous call
  def waitingPhilosopher(hunger, right, left, name, ctrl, waiter) do
    IO.puts("Philosopher #{name} is waiting for chopsticks")
    send(waiter, {self(), left, right})
    receive do
      :ok ->
        IO.puts("Philosopher #{name} received both chopsticks and now shall eat")
        eatingPhilosopher(hunger, right, left, name, ctrl, waiter)
      :no ->
        IO.puts("Philosopher #{name} was asked to wait and so she goes to sleep")
        dreamingPhilosopher(hunger, right, left, name, ctrl, waiter)
    end

  end

  def eatingPhilosopher(hunger, right, left, name, ctrl, waiter) do
    IO.puts("Philosopher #{name} is eating.")
    sleep(@eatingRange)

    send(left, :return)
    send(right, :return)

    IO.puts("Philosopher #{name} has finished eating and will now go back to sleep")
    dreamingPhilosopher(hunger - 1, right, left, name, ctrl, waiter)
  end

  def sleep(0) do :ok end
  def sleep(t) do
    :timer.sleep(:rand.uniform(t))
  end
end

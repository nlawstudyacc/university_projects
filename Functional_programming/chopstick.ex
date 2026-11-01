defmodule Chopstick do
  #location == :available || :gone

  def quit(chopstickName) do
    send(chopstickName, :quit)
  end

  def start do
    spawn_link(fn -> available() end)
  end

  #changed available state to asynchronous section
  def available() do
    receive do
      {:requestWaiter, waiter} ->
        send(waiter, :granted)
        gone()
      :quit -> :ok
    end
  end

  def gone() do
    receive do
      {:requestWaiter, waiter} ->
        send(waiter, :denied)
        gone()
      :return -> available()
      :quit -> :ok
    end
  end
end

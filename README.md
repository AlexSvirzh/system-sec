# System Security & OS Internals Toolkit

*🌍 [English](#english) | 🇷🇺 [Русский](#russian)*

---

<h2 id="english">🇬🇧 English</h2>

A collection of low-level tools and PoCs (Proof of Concepts) exploring Linux/Windows operating system security, virtualization detection, and resource management.

### 🛡️ 1. PAM Duress Module (`/pam-duress-module`)
A custom Pluggable Authentication Module (PAM) for Linux designed to protect sensitive data under physical coercion. Entering a "Panic PIN" simulates a successful login while secretly executing an emergency wipe protocol (`rm -rf`) and alerting the admin via `syslog`.
### 🕵️ 2. Virtual Machine Evasion (`/vm-evasion`)
A PoC demonstrating how to detect if a program is running inside a Virtual Machine (Hyper-V/WSL) using Timing Analysis. Written in x86_64 Assembly, it measures the cycle overhead of `VMExit` events using `CPUID` and `RDTSC`.
### 💥 3. Resource Exhaustion Testing (`/resource-exhaustion`)
Analyzes how Linux and Windows kernels handle severe resource starvation:
*   **Forkbomb:** Compares Linux's lightweight `fork()` vs Windows' heavyweight `CreateProcessA()`.
*   **Membomb:** Demonstrates Linux's "lazy allocation" (OOM Killer intervention) vs Windows' strict `VirtualAlloc` (immediate API failure).

---

<h2 id="russian">🇷🇺 Русский</h2>

Сборник низкоуровневых утилит и PoC (Proof of Concept) для исследования безопасности ОС Linux/Windows, обнаружения виртуализации и управления ресурсами.

### 🛡️ 1. PAM Duress Module (`/pam-duress-module`)
Кастомный PAM-модуль для Linux. Защищает данные при физическом принуждении. При вводе "Panic PIN" система имитирует успешный вход, но скрытно уничтожает защищаемые данные и отправляет алерт в `syslog`.
### 🕵️ 2. Обнаружение виртуализации (`/vm-evasion`)
PoC на x86_64 Assembly для обнаружения работы внутри ВМ (Hyper-V/WSL). Измеряет задержку процессорных тактов (VMExit) при выполнении привилегированных инструкций с помощью `CPUID` и `RDTSC`.
### 💥 3. Стресс-тестирование ресурсов (`/resource-exhaustion`)
Анализ реакции ядер Linux и Windows на исчерпание ресурсов:
*   **Forkbomb:** Сравнение легковесного `fork()` в Linux и тяжелого `CreateProcessA()` в Windows.
*   **Membomb:** Демонстрация "ленивого выделения" в Linux (срабатывание OOM Killer) и строгого выделения в Windows (ошибка API).
